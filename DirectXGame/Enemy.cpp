#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	textureHandle;
	velocity_ = {-kWalkSpeed, 0, 0};
}

void Enemy::Update() { 
	
	worldTransform_.TransferMatrix();
	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdataMatrix(); 
}

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
