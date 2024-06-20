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
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接着状態に移行
			onGround_ = true;
		}
	}

	//
	CollisionMapInfo info;
	info.move = velocity_;
	CollisionMap(info);
	//AdhesionStateSwitching(info);
	velocity_=info.move;


	// 7 旋回制御
	if (trunTime_ > 0.0f) {

		trunTime_ -= 5.0f / 60.0f;

		// 左右自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
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

// Vector3 CollisionPosition(const Vector3& center, Corner corner);

Vector3 CollisionPosition(const Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {

	    {+Player::kWidth / 2.0f, -Player::kHeight / 2.0f, 0},
	    {-Player::kWidth / 2.0f, -Player::kHeight / 2.0f, 0},
	    {+Player::kWidth / 2.0f, +Player::kHeight / 2.0f, 0},
	    {-Player::kWidth / 2.0f, +Player::kHeight / 2.0f, 0},
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}
void Player::CollisionMap(CollisionMapInfo& info) {

	CollisionMapTop(info);
	CollisionMapBottom(info);
	CollisionMapRight(info);
	CollisionMapLeft(info);

	CeilingContact(info);
}
//上
void Player::CollisionMapTop(CollisionMapInfo& info) {

	if (info.move.y <= 0) {
		return;
	}
	std::array<Vector3, static_cast<uint32_t>(Corner ::kNumCorner)> positonsNew;
	for (uint32_t i = 0; i < positonsNew.size(); i++) {
		Vector3 result;
		result.x = worldTransform_.translation_.x + info.move.x;
		result.y = worldTransform_.translation_.y + info.move.y;
		result.z = worldTransform_.translation_.z + info.move.z;
		positonsNew[i] = CollisionPosition(result, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	bool hit = false;
	// 左上
	IndexSet lefIndexSet;
	lefIndexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(lefIndexSet.xIndex, lefIndexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右上
	IndexSet RightIndexSet;
	RightIndexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(RightIndexSet.xIndex, RightIndexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {

		IndexSet indexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kRightTop]);
		Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::max(0.0f, (rect.bottom - worldTransform_.translation_.y) - kHeight / 2 - kBlank);
		info.ceiling = true;
	}
}
//下
void Player::CollisionMapBottom(CollisionMapInfo& info) {

	//下降
	if (info.move.y >= 0) {
		return;
	}
	std::array<Vector3, static_cast<uint32_t>(Corner ::kNumCorner)> positonsNew;
	for (uint32_t i = 0; i < positonsNew.size(); i++) {
		Vector3 result;
		result.x = worldTransform_.translation_.x + info.move.x;
		result.y = worldTransform_.translation_.y + info.move.y;
		result.z = worldTransform_.translation_.z + info.move.z;
		positonsNew[i] = CollisionPosition(result, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	bool hit = false;
	// 左下
	IndexSet lefIndexSet;
	lefIndexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(lefIndexSet.xIndex, lefIndexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右下
	IndexSet RightIndexSet;
	RightIndexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(RightIndexSet.xIndex, RightIndexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {

		IndexSet indexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kRightBottom]);
		Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::min(0.0f, (rect.top - worldTransform_.translation_.y) + kHeight / 2 + kBlank);
		info.landing = true;
	}

}


#pragma warning(push)
#pragma warning(disable : 4100)

void Player::CollisionMapRight(CollisionMapInfo& info) {}

void Player::CollisionMapLeft(CollisionMapInfo& info) {}
#pragma warning(pop)

void Player::JudgmenResultMove(const CollisionMapInfo& info) {

	// 移動
	worldTransform_.translation_ += info.move;
}

void Player::CeilingContact(const CollisionMapInfo& info) {

	if (info.ceiling) {

		velocity_.y = 0;
	}
}

void Player::AdhesionStateSwitching(const CollisionMapInfo& info) {

	
	if (onGround_) {
	
		if (velocity_.y > 0.0f) {
		
			onGround_ = false;

		} else {
			std::array<Vector3, static_cast<uint32_t>(Corner ::kNumCorner)> positonsNew;
			MapChipType mapChipType;
			//真下の当たり判定
			bool hit = false;
			// 左下
			IndexSet lefIndexSet;
			lefIndexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kLeftBottom]);
			mapChipType = mapChipField_->GetMapChipTypeByIndex(lefIndexSet.xIndex, lefIndexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}
			positonsNew[kLeftBottom] + Vector3(0, kMinuteValue, 0);
			// 右下
			IndexSet RightIndexSet;
			RightIndexSet = mapChipField_->GetMapchipIndexsetByPosition(positonsNew[kRightBottom]);
			mapChipType = mapChipField_->GetMapChipTypeByIndex(RightIndexSet.xIndex, RightIndexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}
			positonsNew[kRightBottom] + Vector3(0, kMinuteValue, 0);
			if (!hit) {
			
				onGround_ = false;

			}

		}
	
	} else {
	
		//着地フラグ
		if (info.landing) {

			//着地切り替え
			onGround_ = true;
			//x速度減衰
			velocity_.x *= (1.0f - kAttenuationLanding);
			//y速度０に
			velocity_.y = 0.0f;
		
		}
	
	}

}
