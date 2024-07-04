#pragma once
#include"Model.h"
#include <array>
#include "WorldTransform.h"
#include "mt3.h"
class DeathParticles {
public:
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);
	void Update();
	void Draw();

	private:
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_ = {};
	static inline const uint32_t kNumParticles = 8;
	std::array<WorldTransform, kNumParticles> worldTransforms_;

};
