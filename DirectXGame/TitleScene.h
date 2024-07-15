#pragma once
#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include <Input.h>
#include"titleTx.h"
#include <ViewProjection.h>
#include "Sprite.h"

class TitleScene {
public:
	~TitleScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsFinished() const { return finished_; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool finished_ = false;

	Model* modelText = nullptr;
	TitleText* titleText = nullptr;

	// ビュープロジェクション
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
