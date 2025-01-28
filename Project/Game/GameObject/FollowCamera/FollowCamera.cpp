//#include "FollowCamera.h"
//#include <Input.h>
//#include <Xinput.h>
//#include "VectorCalculation.h"
//#include "Matrix4x4Calculation.h"
//
//void FollowCamera::Initialize() {
//	WinApp::GetInstance();
//	Input::GetInstance();
//
//	viewProjection_.Initialize();
//	viewProjection_.translate_.y = 2.0f;
//	viewProjection_.translate_.z = -10.0f;
//	viewProjection_.rotate_.x = 0.0f;
//}
//
//void FollowCamera::Update() {
//	if (target_) {
//		Vector3 offset = TargetOffset();
//		interTarget_ = Lerp(interTarget_, target_->translate_, 0.1f);
//		viewProjection_.translate_ = Add(interTarget_, offset);
//	}
//
//	const float kRadian = 0.02f;
//
//	destinationAngleY_ += (float)Input::GetJoyRStickPos().x * kRadian;
//	destinationAngleX_ -= (float)Input::GetJoyRStickPos().y * kRadian;
//
//	viewProjection_.rotate_.x = destinationAngleX_;
//	viewProjection_.rotate_.y = destinationAngleY_;
//
//	//float thresHoldRightX = 0.0f;
//	//float thresHoldUpY = 0.0f;
//	//float thresHoldLeftX = 0.0f;
//	//float thresHoldDownY = 0.0f;
//
//	//thresHoldRightX += Input::GetJoyRStickPos().x;
//	//thresHoldUpY += Input::GetJoyRStickPos().y;
//	//thresHoldLeftX += Input::GetJoyRStickPos().x;
//	//thresHoldDownY += Input::GetJoyRStickPos().y;
//
//	/*if (viewProjection_.rotation_.x >= -0.26f && viewProjection_.rotation_.x <= 0.26f) {
//		destinationAngleX_ -= (float)Input::GetJoyRStickPos().y * 0.02f;
//	}
//
//	if (viewProjection_.rotation_.y >= -0.26f && viewProjection_.rotation_.y <= 0.26f) {
//		destinationAngleY_ -= (float)Input::GetJoyRStickPos().x * 0.02f;
//	}*/
//
//	if (viewProjection_.rotate_.x < -0.26f) {
//		viewProjection_.rotate_.x = -0.2599999f;
//	}
//	else if (viewProjection_.rotate_.x > 0.26f) {
//		viewProjection_.rotate_.x = 0.2599999f;
//	}
//
//	/*if (thresHoldRightX > 0.3f || thresHoldLeftX < -0.3f) destinationAngleY_ += (float)Input::GetJoyRStickPos().x * kRadian;
//	if (thresHoldUpY< 0.6f || thresHoldDownY > -0.6f) if (thresHoldUpY > 0.3f || thresHoldDownY < -0.3f) destinationAngleX_ -= (float)Input::GetJoyRStickPos().y * kRadian;*/
//
//	/*viewProjection_.rotation_.y = VectorTransform::Alerp(viewProjection_.rotation_.y, destinationAngleY_, 0.1f);
//	viewProjection_.rotation_.x = VectorTransform::Alerp(viewProjection_.rotation_.x, destinationAngleX_, 0.1f);*/
//
//	//if (viewProjection_.rotation_.x >= -0.3f || viewProjection_.rotation_.x <= 0.3f) {
//	//}
//
//	viewProjection_.Update();
//	viewProjection_.Transfer();;
//}
//
//void FollowCamera::SetTarget(const WorldTransform* target) {
//	target_ = target;
//	Reset();
//}
//
//Vector3 FollowCamera::TargetOffset() const {
//	Vector3 offset = { 0, 2, -30.0f };
//	Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(viewProjection_.rotate_.x, viewProjection_.rotate_.y, viewProjection_.rotate_.z);
//
//	offset = TransformCalculation(offset, rotateMatrix);
//
//	return offset;
//}
//
//void FollowCamera::Reset() {
//	if (target_) {
//		interTarget_ = target_->translate_;
//
//		viewProjection_.rotate_.y = target_->rotate_.y;
//		viewProjection_.rotate_.x = target_->rotate_.x;
//	}
//
//	destinationAngleY_ = viewProjection_.rotate_.y;
//	destinationAngleX_ = viewProjection_.rotate_.x;
//
//	Vector3 offset = TargetOffset();
//	viewProjection_.translate_ = Add(interTarget_, offset);
//}