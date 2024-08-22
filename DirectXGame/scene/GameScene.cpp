#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	for (Enemy* enemy : enemies_) {
		delete enemy;
	};
	// delete enemy_;
	delete skydome_;
	delete modelBlock_;
	delete debugCamera_;
	delete modelSkydome_;
	delete modelPlayer_;
	delete modelEnemy_;
	delete mapChipField_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlocks : worldTransformBlockLine) {
			delete worldTransformBlocks;
		}
	}
	delete deathParticles_;
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {
	// フェーズ
	phase_ = Phase::kPlay;

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("nightSky.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	

	modelBlock_ = Model::Create();
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, &viewProjection_);

	// マップチップ
	mapChipField_ = new MapchipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();
	modelPlayer_ = Model::CreateFromOBJ("Player", true);

	player_ = new Player();
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 17);
	player_->Initialize(modelPlayer_, &viewProjection_, playerPosition);
	player_->SetMapchipField(mapChipField_);


	// プレイヤ配置
	modelEnemy_ = Model::CreateFromOBJ("Enemy", true);
	for (int32_t i = 0; i <70; ++i) {

		Enemy* newEnemy = new Enemy();
		// 敵配置
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(15 + i * 5, 18);
		newEnemy->Initialize(modelEnemy_, &viewProjection_, enemyPosition);
		enemies_.push_back(newEnemy);
	}

	// Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(12, 18);
	// enemy_->Initialize(model_, textureHandle_, &viewProjection_, enemyPosition);

	// カメラコントロール
	movebleArea_ = {17.0f, 179.0f, 9.0f, 50.0f};
	cameraController_ = new CameraController;
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();
	cameraController_->SetMoveableArea(movebleArea_);

	// パーティクル
	deathParticles_ = new DeathParticles;
	modelParticls_ = Model::CreateFromOBJ("perticle", true);
	deathParticles_->Initialize(modelParticls_, &viewProjection_, playerPosition);
}

void GameScene::Update() {
	ChangePhase();
	// フェーズ
	switch (phase_) {
	case Phase::kPlay:
		
		skydome_->Update();

		player_->Update();

		for (Enemy* enemy : enemies_) {
			enemy->Update();
		};

		
		if (player_->GetGool()) {
			finished_ = true;
		}

		cameraController_->Update();

		viewProjection_.matView = cameraController_->GetViewProjection().matView;
		viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlocks : worldTransformBlockLine) {
				if (!worldTransformBlocks)
					continue;
				worldTransformBlocks->matWorld_ = MakeAffineMatrix(worldTransformBlocks->scale_, worldTransformBlocks->rotation_, worldTransformBlocks->translation_);
				worldTransformBlocks->TransferMatrix();
			}
		}
		CheckAllCollision();

		break;
	case Phase::kDeth:
		skydome_->Update();

		for (Enemy* enemy : enemies_) {
			enemy->Update();
		};
		if (deathParticles_) {
			deathParticles_->Update();
		}
		cameraController_->Update();
	
		break;
	default:
		break;
	}

	

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ ^= true;
	}
#endif // DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		//viewProjection_.UpdateMatrix();
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	if (player_->isDead()==false) {
		player_->Draw();
	}

	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	};
	// enemy_->Draw();
	//	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	skydome_->Draw();
	// パーティクル
	if (deathParticles_) {
		deathParticles_->Draw();
	}

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlocks : worldTransformBlockLine) {
			if (!worldTransformBlocks)
				continue;
			modelBlock_->Draw(*worldTransformBlocks, viewProjection_);
		}
	}
	//
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks() {

	// 要素数
	const uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	const uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数の変更
	worldTransformBlocks_.resize(numBlockVirtical);
	// キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; j++) {

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::CheckAllCollision() {

	// 判定対象1,2
	aabb aabb1, aabb2;
	// 自キャラ座標
	aabb1 = player_->GetAABB();
	// 自キャラとEnemyの判定
	for (Enemy* enemy : enemies_) {
		aabb2 = enemy->GetAABB();
		if (IsCollision(aabb1, aabb2)) {

			player_->Oncollision(enemy);
			enemy->OnCollision(player_);
		}
	}
	/*aabb2 = enemy_->GetAABB();
	    if (IsCollision(aabb1, aabb2)) {

	        player_->Oncollision(enemy_);
	        enemy_->OnCollision(player_);

	    }*/
}

void GameScene::ChangePhase() {

	switch (phase_) {
	case Phase::kPlay:
		if (player_->isDead()) {
			//死亡演出フェーズ切り替え
			phase_ = Phase::kDeth;
			//自キャラの座標を獲得
			const Vector3& dethParticlesPosition = player_->GetWorldPosition();
			// 自キャラの座標にデスパーティクル
			deathParticles_ = new DeathParticles;
			// 初期化
			deathParticles_->Initialize(modelParticls_, &viewProjection_, dethParticlesPosition);
		}
		break;
	case Phase::kDeth:
		if (deathParticles_ && deathParticles_->IsFinished()) {

			finished_ = true;
		}
		break;
	default:
		break;
	}
}
