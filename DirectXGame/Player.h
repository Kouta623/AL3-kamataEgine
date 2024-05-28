#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>
#include <numbers>

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
};