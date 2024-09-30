#include "Stage.h"

Stage* Stage::GetInstance()
{
	static Stage instance;
	return &instance;
}

void Stage::Initialize() 
{
	testStageHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");

	testStage_.reset(Model::Create(testStageHandle_));

	testStageTransform_.Initialize();
	testStageTransform_.translate_ = { -3.0f,-0.8f,0.0f };
	testStageTransform_.scale_ = { 0.1f,0.89f,3.0f };

	testStageHandle2_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");

	testStage2_.reset(Model::Create(testStageHandle_));

	testStageTransform2_.Initialize();
	testStageTransform2_.translate_ = { 11.0f,-2.7f,0.0f };
	testStageTransform2_.scale_ = { 8.0f,3.0f,3.0f };

	testStageHandle3_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");

	testStage3_.reset(Model::Create(testStageHandle_));

	testStageTransform3_.Initialize();
	testStageTransform3_.translate_ = { -11.0f,-2.7f,0.0f };
	testStageTransform3_.scale_ = { 8.0f,3.0f,3.0f };

	goalObjectHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/GoalObject", "GoalObject.obj");

	goalObject_.reset(Model::Create(goalObjectHandle_));

	goalObjectTransform_.Initialize();
	goalObjectTransform_.translate_ = { 3.7f,2.13f,0.0f };
	goalObjectTransform_.scale_ = { 0.5f,0.5f,0.5f };

	grabObjectHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/GrabObject", "GrabObject.obj");

	grabObejct_.reset(Model::Create(grabObjectHandle_));

	grabObjectTransform_.Initialize();
	grabObjectTransform_.translate_ = { -1.4f,-0.0f,0.0f };
	grabObjectTransform_.scale_ = { 0.5f,0.5f,0.5f };
}

void Stage::Update()
{
	ImGui::Begin("Stage");
	ImGui::DragFloat3("Translate", &testStageTransform_.translate_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &testStageTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("Scale", &testStageTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("st1Translate", &testStageTransform_.translate_.x, 0.01f);
	ImGui::DragFloat3("st2Translate", &testStageTransform2_.translate_.x, 0.01f);
	ImGui::End();

	SetCollision();
	testStageTransform_.Update();
	testStageTransform2_.Update();
	testStageTransform3_.Update();
	goalObjectTransform_.Update();
	grabObjectTransform_.Update();

	Vector3 move{};
	XINPUT_STATE joyState{};

	
		if (Input::GetInstance()->GetJoystickState(joyState))
		{
			if (Input::GetInstance()->IsPushKey(DIK_RIGHTARROW))
			{
				testStageTransform_.scale_.x += 0.04f;
				testStageTransform_.translate_.x += 0.04f;
			}

			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
			const float kCharacterSpeed = 0.03f;

			if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX > 0.5f)
			{
				move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX,0.0f,0.0f };

			}
			else if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX < -0.5f)
			{
				move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX ,0.0f,0.0f };
			}

			move = Multiply(kCharacterSpeed, Normalize(move));

			grabObjectTransform_.translate_ = Add(move, grabObjectTransform_.translate_);
		}
	}
}

void Stage::Draw(Camera& camera)
{
	testStage_->Draw(testStageTransform_, camera);
	testStage2_->Draw(testStageTransform2_, camera);
	testStage3_->Draw(testStageTransform3_, camera);
	//goalObject_->Draw(goalObjectTransform_, camera);
	//grabObejct_->Draw(grabObjectTransform_, camera);
}

void Stage::SetCollision()
{
	testStageCollision_.center = testStageTransform_.GetWorldPosition();
	GetOrientations(MakeRotateXYZMatrix(testStageTransform_.rotate_.x, testStageTransform_.rotate_.y, testStageTransform_.rotate_.z), testStageCollision_.orientation);
	testStageCollision_.size = { 7.0f,1.4f,1.5f };
};