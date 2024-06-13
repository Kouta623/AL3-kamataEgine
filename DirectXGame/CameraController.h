#pragma once
#include<ViewProjection.h>
#include<WorldTransform.h>
#include <Vector3.h>


class Player;

class CameraController {

public:
	struct Rect {
	
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	
	};
	void Initialize();

	void Update();

	void Reset();

	void SetTarget(Player* target) { target_ = target; }

	void SetMoveableArea(Rect area) { movebleArea_ = area; }
	
	ViewProjection& GetViewProjection() { return viewProjection_; }
private:
	ViewProjection viewProjection_;
	Player* target_ = nullptr;
	Vector3 targetoffset_ = {0, 0, -15.0f};
	Vector3 goalPos_={};
	static inline const float kInterpolationRate = 0.5f;
	static inline const float kVelocityBias = 5;
	//矩形
	Rect movebleArea_ = {0, 100, 0, 100};
	//カメラ移動範囲
	static inline const Rect merge = {-5.0f, 5.0f, 3.0f, 50.0f};
};
