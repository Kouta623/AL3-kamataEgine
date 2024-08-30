#include "TitleScene.h"

TitleScene::~TitleScene() {

	delete titleText;
}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクションの初期化
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// テキスト
	titleText = new TitleText;
	modelText = Model::CreateFromOBJ("title", true);
	titleText->Initialize(modelText, &viewProjection_);


	titleText2 = new TitleText2;
	modelText2 = Model::CreateFromOBJ("title2", true);
	titleText2->Initialize(modelText2, &viewProjection_);

	titleText3 = new TitleText3;
	modelText3 = Model::CreateFromOBJ("title3", true);
	titleText3->Initialize(modelText3, &viewProjection_);

	titleText4 = new TitleText4;
	modelText4 = Model::CreateFromOBJ("title4", true);
	titleText4->Initialize(modelText4, &viewProjection_);
}

void TitleScene::Update() {

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	titleText->Update();
	titleText2->Update();
	titleText3->Update();
	titleText4->Update();



}

void TitleScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	titleText->Draw();
	titleText2->Draw();
	titleText3->Draw();
	titleText4->Draw();

	// fade_->Draw(commandList);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

}
