#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "mt3.h"
#include "Model.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>
#include "Player.h"
#include "TextureManager.h"
#include <cassert>
#include "MapchipField.h"
#include "CameraController.h"
#include"Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void GenerateBlocks();

private: // メンバ変数
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	uint32_t enemyTextureHandle_=0;
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;

	Model* modelBlock_ = nullptr;
	uint32_t blockTextureHandle_ = 0u;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	//マップチップフィールド
	MapchipField* mapChipField_;
	//カメラコントロール
	CameraController* cameraController_;
	
	CameraController::Rect movebleArea_ = {};
};
