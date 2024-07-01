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
#include <imgui.h>
#include"AABB.h"
class MapchipField;
class Player;


class Enemy {
public:

	Enemy();
	~Enemy();

	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void SetMapchipField(MapchipField* mapChipField) { mapChipField_ = mapChipField; }
	
	Vector3 GetWorldPosition();
	aabb GetAABB();

	void OnCollision(const Player* player);
	

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	// マップチップによるフィールド
	MapchipField* mapChipField_ = nullptr;

	//スピード
	static inline const float kWalkSpeed = 0.1f;
	//アニメーション
	//最初
	static inline const float kWalkMotionAngleStart = -30.0f;
	//最後
	static inline const float kWalkMotionAngleend= 30.0f;
	//周期
	static inline const float kwalkMotionTime= 1.0f;

	//経過時間
	float walkTimer_ = 0.0f;

	static inline const float kWidth = 2.0f;
	static inline const float kHeight = 2.0f;
};
