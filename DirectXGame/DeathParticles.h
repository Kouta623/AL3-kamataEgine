#pragma once
#include"Model.h"
#include <array>
#include "WorldTransform.h"
#include "mt3.h"
#include <algorithm>


class DeathParticles {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	void Update();
	void Draw();
	bool IsFinished() const { return isFinished_; }
	private:
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	static inline const uint32_t kNumParticles = 8;
	std::array<WorldTransform, kNumParticles> worldTransforms_;

	// 存続時間
	static inline const float kDuration =2.0f;
	// 移動の速さ
	static inline const float kSpeed = 0.1f;
	// 分割した一個分の角度
	static inline const float kAguleUnut = 2.0f * 3.14f / kNumParticles;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間
	float count_ = 0.0f;
	//色変更オブジェクト
	ObjectColor objectColor_;
	//色の数値
	Vector4 color_;

	bool finished_ = false;
};
