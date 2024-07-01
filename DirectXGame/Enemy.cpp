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
	walkTimer_ = 0.0f;
}

void Enemy::Update() {

	// タイマー加算
	walkTimer_ += 1.0f / 60.0f;
	// 回転アニメーション
	float param = std::sin((2*3.14f)*walkTimer_/kwalkMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleend * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = (radian) * 3.14f / 360;

	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdataMatrix();
}

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

aabb Enemy::GetAABB() {

	Vector3 worldPos = GetWorldPosition();
	aabb AABB;

	AABB.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kWidth / 2.0f, worldPos.z - kWidth / 2.0f};
	AABB.max = {worldPos.x + kHeight / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kHeight / 2.0f};
	return AABB;
}

void Enemy::OnCollision(const Player* player) { (void)player; }
