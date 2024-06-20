#pragma once
#define NOMINMAX
#include "Input.h"
#include "MapchipField.h"
#include "Model.h"
#include "WorldTransform.h"
#include <ViewProjection.h>
#include <algorithm>
#include <cassert>
#include <numbers>
class MapchipField;

enum class LRDirection {
	kRight,
	kLeft,
};

struct CollisionMapInfo {

	bool ceiling = false;
	bool landing = false;
	bool hitwall = false;
	Vector3 move;
};

enum Corner {

	kRightBottom, // 右上
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner

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

	WorldTransform& GetWorldTransform() { return worldTransform_; }
	// 速度加算
	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapchipField(MapchipField* mapChipField) { mapChipField_ = mapChipField; }

	// キャラクター当たり判定

	static inline const float kWidth = 1.9f;
	static inline const float kHeight = 1.9f;

	static inline const float kBlank = 0.1f;
	// 判定結果を判定して移動させる
	void JudgmenResultMove(const CollisionMapInfo& info);
	// 天井接触
	void CeilingContact(const CollisionMapInfo& info);
	//接着状態切り替え
	void AdhesionStateSwitching(const CollisionMapInfo& info);

private:
	void CollisionMap(CollisionMapInfo& info);
	void CollisionMapTop(CollisionMapInfo& info);
	void CollisionMapBottom(CollisionMapInfo& info);
	void CollisionMapRight(CollisionMapInfo& info);
	void CollisionMapLeft(CollisionMapInfo& info);

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};

	LRDirection lrDirecton_ = LRDirection::kRight;

	static inline const float kAcceleration = 0.04f;
	static inline const float kAttenuation = 0.3f;
	static inline const float kLimitRunSpeed = 1.0f;

	// 旋回開始時角度
	float trunFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float trunTime_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimaeTurn = 1.0f;

	// 着地フラグ
	bool onGround_ = true;
	// 重力加速度
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度
	static inline const float kLimitFallSpeed = 1.0f;
	// ジャンプ初速
	static inline const float kJumpAcceleration = 1.5f;
	// マップチップによるフィールド
	MapchipField* mapChipField_ = nullptr;
	//着地速度減衰
	static inline const float kAttenuationLanding = 0.1f;
	//微小な値
	static inline const float kMinuteValue = -0.1f;
};