#include "cmath"
#include "numbers"
#include "titleTx4.h"
void TitleText4::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {5, 5, 5};
	worldTransform_.translation_ = {8, 0, 0};
	worldTransform_.rotation_.x = -(std::numbers::pi_v<float> / 2.0f);
}

void TitleText4::Update() { worldTransform_.UpdataMatrix(); }

void TitleText4::Draw() { model_->Draw(worldTransform_, *viewProjection_); }