#pragma once
#define NOMINMAX
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#include<ViewProjection.h>

enum class LRDirection {
	kRight,
	kLeft,
};


class Player {
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャーハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};

	LRDirection lrDirecton_ = LRDirection::kRight;

	static inline const float kAcceleration = 0.04f;
	static inline const float kAttenuation = 0.3f;
	static inline const float kLimitRunSpeed = 1.0f;

	//旋回開始時角度
	float trunFirstRotationY_ = 0.0f;
	//旋回タイマー
	float trunTime_ = 0.0f;
	//旋回時間<秒>
	static inline const float kTimaeTurn = 1.0f;
	
	//着地フラグ
	bool onGround_ = true;
	//重力加速度
	static inline const float kGravityAcceleration = 0.2f;
	//最大落下速度
	static inline const float kLimitFallSpeed = 1.0f;
	//ジャンプ初速
	static inline const float kJumpAcceleration = 2.0f;
};