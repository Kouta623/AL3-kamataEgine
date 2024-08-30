#include "titleTx2.h"
#include "cmath"
#include "numbers"
void TitleText2::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {5, 5, 5};
	worldTransform_.translation_ = {-10, 0, 0};
	worldTransform_.rotation_.x = -(std::numbers::pi_v<float> / 2.0f);
}

void TitleText2::Update() { worldTransform_.UpdataMatrix(); }

void TitleText2::Draw() { model_->Draw(worldTransform_, *viewProjection_); }