#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include <cassert>
#include<numbers>
#include<algorithm>


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
	void Initialize(Model* model, ViewProjection* viewProjection,const Vector3& position);

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
	static inline const float kAcceleration = 20;
	static inline const float kAttenuation = 20;
	static inline const float kLimitRunSpeed = 20;

	LRDirection lrDirecton = LRDirection::kRight;

};