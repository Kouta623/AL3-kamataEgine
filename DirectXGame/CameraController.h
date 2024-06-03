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

	

private:
	ViewProjection *viewProjection_;
	Player* target_ = nullptr;
	void SetTarget(Player* target) { target_ = target; }
	Vector3 targetoffset_ = {0, 0, -15.0f};

};
