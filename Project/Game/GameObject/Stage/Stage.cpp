#include "Stage.h"

Stage* Stage::GetInstance()
{
	static Stage instance;
	return &instance;
}

void Stage::Initialize() 
{
	moveWallHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");
	moveWall_.reset(Model::Create(moveWallHandle_));

	moveWallTransform_.Initialize();
	moveWallTransform_.translate_ = { 5.67f,3.00f,0.00f };
	moveWallTransform_.rotate_ = { 0.00f,0.00f,1.58f };
	moveWallTransform_.scale_ = { 3.44f,4.72f,3.02f };

	pushBackWallHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");
	pushBackWall_.reset(Model::Create(pushBackWallHandle_));

	pushBackWallTransform_.Initialize();
	pushBackWallTransform_.translate_ = { -2.60f,3.00f,0.00f };
	pushBackWallTransform_.rotate_ = { 0.00f,0.00f,1.58f };
	pushBackWallTransform_.scale_ = { 3.44f,4.72f,3.02f };

	pushBackWallHandle2_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");
	pushBackWall2_.reset(Model::Create(pushBackWallHandle_));

	pushBackWallTransform2_.Initialize();
	pushBackWallTransform2_.translate_ = { 9.20f,3.00f,0.00f };
	pushBackWallTransform2_.rotate_ = { 0.00f,0.00f,1.58f };
	pushBackWallTransform2_.scale_ = { 3.44f,4.72f,3.02f };

	testStageHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");
	testStage_.reset(Model::Create(testStageHandle_));

	testStageTransform_.Initialize();
	testStageTransform_.translate_ = { 0.0f,-2.7f,0.0f };
	testStageTransform_.scale_ = { 8.0f,3.0f,3.0f };

	goalObjectHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/GoalObject", "GoalObject.obj");

	goalObject_.reset(Model::Create(goalObjectHandle_));

	goalObjectTransform_.Initialize();
	goalObjectTransform_.translate_ = { 4.6f,-0.2f,0.0f };
	goalObjectTransform_.scale_ = { 0.5f,0.5f,0.5f };

	grabObjectHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Touch", "Touch.obj");

	grabObejct_.reset(Model::Create(grabObjectHandle_));

	grabObjectTransform_.Initialize();
	grabObjectTransform_.translate_ = { -3.7f,-0.2f,0.0f };
	grabObjectTransform_.scale_ = { 0.5f,0.5f,0.5f };
	grabObjectTransform_.rotate_ = { 0.0f,0.0f,1.54f };

	backObjectHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Plane", "plane.obj");

	backObject_.reset(Model::Create(backObjectHandle_));

	backObjectTransform_.Initialize();
	backObjectTransform_.translate_ = { 0.0f,0.0f,3.0f };
	backObjectTransform_.scale_ = { 20.0f,20.0f,10.0f };

	backObjectHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Title/Object1.png");

	object1Transform_ = { 10.0f,10.0f };

	object1_.reset(Sprite::Create(backObjectHandle_,object1Transform_));

	surfaceBackHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Plane", "Plane.gltf");
	surfaceBack_.reset(Model::Create(surfaceBackHandle_));

	surfaceBackTransform_.Initialize();
	surfaceBackTransform_.translate_ = { 0.0f,0.0f,0.8f };
	surfaceBackTransform_.rotate_ = { -1.44f,0.0f,0.0f };
	surfaceBackTransform_.scale_ = { 10.260f,6.140f,7.630f };
	surfaceBack_->SetColor({ 1.0f,1.0f,0.0f,1.0f });

	bottonBottomHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/GoalObject", "GoalObject.obj");
	bottonBottom_.reset(Model::Create(bottonBottomHandle_));

	bottonBottomTransform_.Initialize();
	bottonBottomTransform_.translate_ = { 0.29f,0.0f,0.8f };
	bottonBottomTransform_.rotate_ = { 0.0f,0.0f,0.0f };
	bottonBottomTransform_.scale_ = { 0.3f,0.3f,0.3f };

	bottonTopHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");
	bottonTop_.reset(Model::Create(bottonTopHandle_));

	bottonTopTransform_.Initialize();
	bottonTopTransform_.translate_ = { 0.3f,-3.88f,0.8f };
	bottonTopTransform_.rotate_ = { 0.0f,0.0f,0.0f };
	bottonTopTransform_.scale_ = { 0.7f,5.32f,1.0f };
}

void Stage::Update()
{
	/*ImGui::Begin("Stage");
	ImGui::DragFloat3("Translate", &moveWallTransform_.translate_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &bottonBottomTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("Scale", &bottonBottomTransform_.scale_.x, 0.01f);

	ImGui::DragFloat3("WTranslate", &bottonTopTransform_.translate_.x, 0.01f);
	ImGui::DragFloat3("WRotate", &bottonTopTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("WScale", &bottonTopTransform_.scale_.x, 0.01f);
	ImGui::End();*/

	testStageTransform_.Update();
	goalObjectTransform_.Update();
	grabObjectTransform_.Update();
	backObjectTransform_.Update();
	surfaceBackTransform_.Update();
	moveWallTransform_.Update();
	pushBackWallTransform_.Update();
	pushBackWallTransform2_.Update();

	bottonBottomTransform_.Update();
	bottonTopTransform_.Update();

	Vector3 move{};
	XINPUT_STATE joyState{};

	if (isMoveWall_ == true)
	{
		moveWallTransform_.translate_.y += 0.02f;
	}

	if (moveWallTransform_.translate_.y > 8.0f)
	{
		isMoveWall_ = false;
	}

	if (Input::GetInstance()->GetJoystickState(joyState))
	{
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

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			grabObjectTransform_.translate_.y = 1.5f;
			grabObjectTransform_.rotate_.z = 0.0f;
		}
		else
		{
			grabObjectTransform_.translate_.y = -0.2f;
			grabObjectTransform_.rotate_.z = 1.54f;
		}

		if ((float)joyState.Gamepad.sThumbRX / SHRT_MAX > 0.2f)
		{
			grabObjectTransform_.rotate_.z += (float)joyState.Gamepad.sThumbRX / SHRT_MAX;
		}
		else if ((float)joyState.Gamepad.sThumbRX / SHRT_MAX < -0.2f)
		{
			grabObjectTransform_.rotate_.z += (float)joyState.Gamepad.sThumbRX / SHRT_MAX;
		}
	}
}

void Stage::Draw(Camera& camera)
{
	testStage_->Draw(testStageTransform_, camera);
	goalObject_->Draw(goalObjectTransform_, camera);
	//grabObejct_->Draw(grabObjectTransform_, camera);
	backObject_->Draw(backObjectTransform_, camera);
	//object1_->Draw();

	surfaceBack_->Draw(surfaceBackTransform_, camera);
	moveWall_->Draw(moveWallTransform_, camera);
	pushBackWall_->Draw(pushBackWallTransform_,camera);
	pushBackWall2_->Draw(pushBackWallTransform2_, camera);

	bottonBottom_->Draw(bottonBottomTransform_, camera);
	bottonTop_->Draw(bottonTopTransform_, camera);
}

void Stage::SetCollision()
{
	testStageCollision_.center = testStageTransform_.GetWorldPosition();
	GetOrientations(MakeRotateXYZMatrix(testStageTransform_.rotate_.x, testStageTransform_.rotate_.y, testStageTransform_.rotate_.z), testStageCollision_.orientation);
	testStageCollision_.size = { 8.0f,2.0f,2.0f };
};