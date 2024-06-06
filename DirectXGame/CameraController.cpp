#include "CameraController.h"
#include "Player.h"
void CameraController::Initialize() { viewProjection_.Initialize(); }

void CameraController::Update() {

	const WorldTransform& targetWorldTransfome = target_->GetWorldTransform();
	viewProjection_.translation_.x = targetWorldTransfome.translation_.x + targetoffset_.x;
	viewProjection_.translation_.y = targetWorldTransfome.translation_.y + targetoffset_.y;
	viewProjection_.translation_.z = targetWorldTransfome.translation_.z + targetoffset_.z;
					
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


