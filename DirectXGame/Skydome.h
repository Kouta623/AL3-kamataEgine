#pragma once
#include "ViewProjection.h"
#include <WorldTransform.h>
#include <ViewProjection.h>
#include <assert.h>
#include <Model.h>

class Skydome {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);
	
	void Update();
	
	void Draw();

private:
	WorldTransform worldTransform_;
	ViewProjection *viewProjection_ = nullptr;

	Model* model_ = nullptr;
};
