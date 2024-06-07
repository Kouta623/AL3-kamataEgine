#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	textureHandle;

}

void Player::Update() {
	worldTransform_.TransferMatrix();
	if (onGround_) {
		// 移動入力
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				if (lrDirecton_ != LRDirection::kRight) {

					lrDirecton_ = LRDirection::kRight;
				}
				// 左右状態切り替え
				trunFirstRotationY_ = worldTransform_.rotation_.y;
				trunTime_ = kTimaeTurn;

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirecton_ != LRDirection::kLeft) {

					lrDirecton_ = LRDirection::kLeft;
				}
				// 左右状態切り替え
				trunFirstRotationY_ = worldTransform_.rotation_.y;
				trunTime_ = kTimaeTurn;
			}

			// 加減速
			velocity_ += acceleration;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			velocity_.x *= (1.0f - kAttenuation);
		}

		if (Input::GetInstance()->TriggerKey(DIK_UP)) {
			velocity_ += Vector3(0, kJumpAcceleration, 0);
		}

		// 行列計算

	} else {
		// 落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	bool landing = false;
	// 地面にとの当たり判定
	if (velocity_.y < 0) {
		// Yが地面以下になったら着地
		if (worldTransform_.translation_.y <= 2.0f) {
			landing = true;
		}
	}

	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		}
	} else {
		if (landing) {
			// 埋め込み排斥
			worldTransform_.translation_.y = 2.0f;
			// 摩擦で横方向速度が減衰
			velocity_.x *= (1.0f - kAttenuation);
			//下方向速度をリセット
			velocity_.y = 0.0f;
			//接着状態に移行
			onGround_ = true;
		}
	}

	// 旋回制御
	if (trunTime_ > 0.0f) {

		trunTime_ -= 5.0f / 60.0f;

		// 左右自キャラ角度テーブル
		float destinationRotationYTable[] = {
			std::numbers::pi_v<float> / 2.0f, 
			std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた目標角度を取得
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirecton_)];
		// 自キャラ角度を設定
		worldTransform_.rotation_.y = (1.0f - trunTime_) * destinationRotationY + trunTime_ * trunFirstRotationY_;
	}

			// 移動
	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdataMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
