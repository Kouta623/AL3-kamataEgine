#include "titleTx3.h"
#include "cmath"
#include "numbers"
void TitleText3::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {5, 5, 5};
	worldTransform_.translation_ = {-4, 0, 0};
	worldTransform_.rotation_.x = -(std::numbers::pi_v<float> / 2.0f);
}

void TitleText3::Update() { worldTransform_.UpdataMatrix(); }

void TitleText3::Draw() { model_->Draw(worldTransform_, *viewProjection_); }