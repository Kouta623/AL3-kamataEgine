#include "DeathParticles.h"

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	// フェードアウト
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void DeathParticles::Update() {
	//終了なら何もしない
	if (isFinished_) {
		return;
	}
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdataMatrix();
	}

	for (uint32_t i = 0; i < kNumParticles; i++) {
		//基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0.0};
		//回転角度計算
		float angle = kAguleUnut * i;
		//z軸まわり回転行列
		Matrix4x4 matrixRotation = RotationZ(angle);
		//基本ベクトルを回転させて速度ベクトルを取得
		velocity = Transform(velocity, matrixRotation);
		//移動
		worldTransforms_[i].translation_ += velocity;
	
	}
	//カウンターを1フレーム分の秒数進める
	count_ += 1.0f / 60.0f;
	//存続時間の上限に達したら
	if (count_ >= kDuration) {
		count_ = kDuration;
		//終了扱い
		isFinished_ = true;
	}
	//パーティクル
	color_.w -= 0.006f;
	//フェードアウト
	color_.w = std::clamp(color_.w, 0.0f, 1.0f);
	//色変更オブジェクトに色の変更の数値を設定
	objectColor_.SetColor(color_);
	//色変更オブジェクトをVRAM
	objectColor_.TransferMatrix();

}

void DeathParticles::Draw() {
	// 終了なら何もしない
	if (isFinished_) {
		return;
	}


	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_,&objectColor_);
	}
}
