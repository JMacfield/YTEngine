#include "DrawSystem.h"
#include <PipelineManager.h>

DrawSystem::DrawSystem() {

}

void DrawSystem::Initialize() {

	//ここでBufferResourceを作る
	//頂点を6に増やす
	vertexResouce_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(LineVertexData) * 2);
	////マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
	materialResource_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(LineMaterial));

	color_ = { 1.0f,1.0f,1.0f,1.0f };

	//WVP用のリソースを作る。Matrix4x4　1つ分のサイズを用意する
	wvpResource_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(LineTransformMatrix));

	//頂点バッファビューを作成する
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResouce_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点３つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(LineVertexData) * 2;
	//１頂点あたりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(LineVertexData);


	//パイプライン
	PipelineManager::GetInstance()->GenaratedLinePSO();
}




//描画
void DrawSystem::Draw(Vector3 start, Vector3 end, Camera& camera) {


	//U(x)V(y)
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootSignature(PipelineManager::GetInstance()->GetLineRootSignature().Get());
	DirectXCommon::GetInstance()->GetCommandList()->SetPipelineState(PipelineManager::GetInstance()->GetLineGraphicsPipelineState().Get());

	//書き込むためのアドレスを取得
	vertexResouce_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	//左下
	vertexData_[0].position = { start.x,start.y,0.0f,1.0f };
	//上
	vertexData_[1].position = { end.x,end.y,0.0f,1.0f };

	//マテリアルにデータを書き込む


	//書き込むためのアドレスを取得

	LineMaterial* materialData_ = nullptr;
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));

	materialData_->color = color_;

	materialResource_->Unmap(0, nullptr);

	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, start);
	//遠視投影行列
	//Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.5f, float() / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);
	//Matrix4x4 worldMatrix = MakeAffineMatrix();
	//遠視投影行列
	Matrix4x4 viewMatrixSprite = MakeIdentity4x4();

	Matrix4x4 projectionMatrixSprite = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->GetClientWidth()), float(WinApp::GetInstance()->GetClientHeight()), 0.0f, 100.0f);


	//WVP行列を作成
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrixSprite, projectionMatrixSprite));

	//書き込む為のアドレスを取得
	wvpResource_->Map(0, nullptr, reinterpret_cast<void**>(&wvpData_));



	//さっき作ったworldMatrixの情報をここに入れる
	wvpData_->WVP = MakeIdentity4x4();
	wvpData_->World = worldMatrix;




	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	//マテリアルCBufferの場所を設定

	//CBVを設定する
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, wvpResource_->GetGPUVirtualAddress());

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, camera.bufferResource_->GetGPUVirtualAddress());

	//マテリアル
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(2, materialResource_->GetGPUVirtualAddress());


	//描画(DrawCall)6頂点で１つのインスタンス。
	DirectXCommon::GetInstance()->GetCommandList()->DrawInstanced(2, 1, 0, 0);

}


DrawSystem::~DrawSystem() {

}
