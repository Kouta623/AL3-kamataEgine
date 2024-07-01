#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	for (Enemy* enemy : enemies_) {
		delete enemy;
	};
	//delete enemy_;
	delete skydome_;
	delete modelBlock_;
	delete debugCamera_;
	delete modelSkydome_;
	delete mapChipField_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlocks : worldTransformBlockLine) {
			delete worldTransformBlocks;
		}
	}

	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	player_ = new Player();

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

	player_->SetMapchipField(mapChipField_);
	//プレイヤ配置
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);
	player_->Initialize(model_,textureHandle_, &viewProjection_, playerPosition);


	for (int32_t i = 0; i < 3; ++i) {
	
		Enemy* newEnemy = new Enemy();
		// 敵配置
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(8+i*5, 18);
		newEnemy->Initialize(model_, textureHandle_, &viewProjection_, enemyPosition);
		enemies_.push_back(newEnemy);
	}
	
	//Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(12, 18);
	//enemy_->Initialize(model_, textureHandle_, &viewProjection_, enemyPosition);

	//カメラコントロール
	movebleArea_ = {17.0f, 179.0f, 9.0f, 50.0f};
	cameraController_ = new CameraController;
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();
	cameraController_->SetMoveableArea(movebleArea_);


	
}

void GameScene::Update() {

	skydome_->Update();
	player_->Update();
	for (Enemy* enemy : enemies_) {
		enemy->Update();
	};

	//enemy_->Update();
	CheckAllCollision();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlocks : worldTransformBlockLine) {
			if (!worldTransformBlocks)
				continue;
			worldTransformBlocks->matWorld_ = MakeAffineMatrix(worldTransformBlocks->scale_, worldTransformBlocks->rotation_, worldTransformBlocks->translation_);
			worldTransformBlocks->TransferMatrix();
		}
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
		viewProjection_.UpdateMatrix();
	}
	cameraController_->Update();

	viewProjection_.matView = cameraController_->GetViewProjection().matView;
	viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();
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
	player_->Draw();
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	};
	//enemy_->Draw();
	    //	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	skydome_->Draw();

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
	
	//判定対象1,2
	aabb aabb1, aabb2;
	//自キャラ座標
	aabb1 = player_->GetAABB();
	//自キャラとEnemyの判定
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
