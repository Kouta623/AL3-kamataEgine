#pragma once
#include<ViewProjection.h>
#include<WorldTransform.h>
#include <Vector3.h>

class Player;

class CameraController {

public:
	void Initialize(ViewProjection* viewProjection);

	void Update();

	void Reset();

	/*void SetMoveableArea() {movebleArea_=}*/
	

private:
	ViewProjection *viewProjection_;
	Player* target_ = nullptr;
	void SetTarget(Player* target) { target_ = target; }
	Vector3 targetoffset_ = {0, 0, -15.0f};

	////矩形
	//struct Rect {
	//
	//	float left = 0.0f;
	//	float right = 1.0f;
	//	float bottom = 0.0f;
	//	float top = 1.0f;
	//
	//};
	//Rect movebleArea_ = {0, 100, 0, 100};
};
