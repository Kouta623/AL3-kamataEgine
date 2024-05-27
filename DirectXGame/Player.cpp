#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {
	worldTransform_.TransferMatrix();
	// 移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)){
			if (velocity_.x < 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x += kAcceleration;
		} 
		else if(Input::GetInstance()->PushKey(DIK_LEFT)){
			if (velocity_.x < 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kAcceleration;
		}
		//加減速
		velocity_+=acceleration;

		//最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	
	} else {
		velocity_.x *= (1.0f - kAttenuation);
	}
	// 移動
	worldTransform_.translation_ = velocity_;
	// 行列計算
	worldTransform_.UpdataMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
