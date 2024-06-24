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
class MapchipField;

class Enemy {
public:

	Enemy();
	~Enemy();

	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void SetMapchipField(MapchipField* mapChipField) { mapChipField_ = mapChipField; }
	

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
	static inline const float kWalkMotionAngleStart = 0.1f;
	static inline const float kWalkMotionAngleend= 0.1f;
	static inline const float kwalkMotionTime= 1.0f;
};
