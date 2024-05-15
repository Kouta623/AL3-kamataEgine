#include "GameScene.h"
#include "Player.h"
#include "TextureManager.h"
#include <cassert>
#include <mt3.h>

GameScene::GameScene() {
	delete model_;
	delete player_;
	delete modelBlock_;
	for (WorldTransform* worldTransformBlocks : worldTransformBlocks_) {
		delete worldTransformBlocks;
	}
	worldTransformBlocks_.clear();
}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	player_ = new Player();
	player_->Initialize(model_, textureHandle_, &viewProjection_);

	modelBlock_ = Model::Create();
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");
	// 要素数
	const uint32_t kNumBlockHorizontal = 20;
	// ブロックい1つの横幅
	const float kBlockWidth = 2.0f;
	// 要素数の変更
	worldTransformBlocks_.resize(kNumBlockHorizontal);
	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; ++i) {

		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}
}

void GameScene::Update() { 

	player_->Update(); 

	for (WorldTransform* worldTransformBlocks: worldTransformBlocks_) {
		worldTransformBlocks->matWorld_ = MakeAffineMatrix(worldTransformBlocks->scale_, worldTransformBlocks->rotation_, worldTransformBlocks->translation_);
		worldTransformBlocks->TransferMatrix();
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
	player_->Draw();
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	for (WorldTransform* worldTransformBlocks : worldTransformBlocks_) {
		modelBlock_->Draw(*worldTransformBlocks, viewProjection_);
	}
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
