#include "DeathParticles.h"

void DeathParticles::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {

	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
}

void DeathParticles::Update() {}

void DeathParticles::Draw() {}
