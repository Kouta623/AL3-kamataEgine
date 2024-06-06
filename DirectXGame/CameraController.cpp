#include "CameraController.h"
#include "Player.h"
void CameraController::Initialize() { viewProjection_.Initialize(); }

void CameraController::Update() {

	const WorldTransform& targetWorldTransfome = target_->GetWorldTransform();
	goalPos_.x = targetWorldTransfome.translation_.x + targetoffset_.x + targetVelocity*kVelocityBias;
	goalPos_.y = targetWorldTransfome.translation_.y + targetoffset_.y+targetVelocity * kVelocityBias;
	goalPos_.z = targetWorldTransfome.translation_.z + targetoffset_.z + targetVelocity * kVelocityBias;
	//追従
	viewProjection_.translation_.x = Larp(viewProjection_.translation_.x, goalPos_.x, kInterpolationRate);			
	viewProjection_.translation_.y = Larp(viewProjection_.translation_.y, goalPos_.y, kInterpolationRate);			
	viewProjection_.translation_.z = Larp(viewProjection_.translation_.z, goalPos_.z, kInterpolationRate);				
	//制限		  
	viewProjection_.translation_.x = max(viewProjection_.translation_.x, movebleArea_.left);
	viewProjection_.translation_.x = min(viewProjection_.translation_.x, movebleArea_.right);
	viewProjection_.translation_.y = max(viewProjection_.translation_.y, movebleArea_.bottom);
	viewProjection_.translation_.y = min(viewProjection_.translation_.y, movebleArea_.top);

	//更新
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {

	const WorldTransform& targetWorldTransfome = target_->GetWorldTransform();
	viewProjection_.translation_.x = targetWorldTransfome.translation_.x + targetoffset_.x;
	viewProjection_.translation_.y = targetWorldTransfome.translation_.y + targetoffset_.y;
	viewProjection_.translation_.z = targetWorldTransfome.translation_.z + targetoffset_.z;


}


