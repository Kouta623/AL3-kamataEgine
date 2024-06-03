#include "CameraController.h"
#include "Player.h"
void CameraController::Initialize(ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

void CameraController::Update() {

	const WorldTransform& targetWorldTransfome = target_->GetWorldTransform();
	viewProjection_->translation_.x = targetWorldTransfome.translation_.x + targetoffset_.x;
	viewProjection_->translation_.y = targetWorldTransfome.translation_.y + targetoffset_.y;
	viewProjection_->translation_.z = targetWorldTransfome.translation_.z + targetoffset_.z;
	viewProjection_->UpdateMatrix();
}

void CameraController::Reset() {

	const WorldTransform& targetWorldTransfome = target_->GetWorldTransform();
	viewProjection_->translation_.x = targetWorldTransfome.translation_.x + targetoffset_.x;
	viewProjection_->translation_.y = targetWorldTransfome.translation_.y + targetoffset_.y;
	viewProjection_->translation_.z = targetWorldTransfome.translation_.z + targetoffset_.z;


}
