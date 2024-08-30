#pragma once
#include "mt3.h"
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>

class TitleText4 {

public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;

	// モデル
	Model* model_ = nullptr;
};
