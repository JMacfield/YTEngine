#include "SkyBox.h"

#include "VectorCalculation.h"
#include "WorldTransform.h"
#include "Camera.h"

#include "DirectXCommon.h"
#include "PipelineManager.h"
#include <TextureManager.h>

void SkyBox::Create(uint32_t textureHandle) 
{
	PipelineManager::GetInstance()->GenerateSkyBoxPSO();

	SURFACE_AMOUNT = 6;
	
	//ここでBufferResourceを作る
	vertexResource_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(VertexData) * SURFACE_VERTEX_ * SURFACE_AMOUNT);

	//頂点バッファビューを作成する
	//リソースの先頭のアドレスから使う
	vertexBufferViewSphere_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点３つ分のサイズ
	vertexBufferViewSphere_.SizeInBytes = sizeof(VertexData) * SURFACE_VERTEX_ * SURFACE_AMOUNT;
	//１頂点あたりのサイズ
	vertexBufferViewSphere_.StrideInBytes = sizeof(VertexData);

	//書き込み用のアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	vertexData_[0].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[1].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[2].position = { 1.0f,-1.0f,1.0f,1.0f };

	vertexData_[3].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData_[4].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[5].position = { 1.0f,-1.0f,-1.0f,1.0f };


	////左面
	//vertexData_[4].position = { -1.0f,1.0f,-1.0f,1.0f };
	//vertexData_[5].position = { -1.0f,1.0f,1.0f,1.0f };
	//vertexData_[6].position = { -1.0f,-1.0f,-1.0f,1.0f };
	//vertexData_[7].position = { -1.0f,-1.0f,1.0f,1.0f };

	vertexData_[6].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData_[7].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData_[8].position = { -1.0f,-1.0f,-1.0f,1.0f };

	vertexData_[9].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[10].position = { -1.0f,-1.0f,-1.0f,1.0f };
	vertexData_[11].position = { -1.0f,1.0f,1.0f,1.0f };


	//前面
	//vertexData_[8].position = { -1.0f,1.0f,1.0f,1.0f };
	//vertexData_[9].position = { 1.0f,1.0f,1.0f,1.0f };
	//vertexData_[10].position = { -1.0f,-1.0f,1.0f,1.0f };
	//vertexData_[11].position = { 1.0f,-1.0f,1.0f,1.0f };

	vertexData_[12].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData_[13].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[14].position = { -1.0f,-1.0f,1.0f,1.0f };

	vertexData_[15].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData_[16].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[17].position = { 1.0f,1.0f,1.0f,1.0f };


	//後は自力で
	//後面。
	//vertexData_[12].position = { 1.0f,1.0f,-1.0f,1.0f };
	//vertexData_[13].position = { -1.0f,1.0f,-1.0f,1.0f };
	//vertexData_[14].position = { 1.0f,-1.0f,-1.0f,1.0f };
	//vertexData_[15].position = { -1.0f,-1.0f,-1.0f,1.0f };
	//
	//vertexData_[12].position = { -1.0f,1.0f,-1.0f,1.0f };
	//vertexData_[13].position = { 1.0f,1.0f,-1.0f,1.0f };
	//vertexData_[14].position = { -1.0f,-1.0f,-1.0f,1.0f };
	//vertexData_[15].position = { 1.0f,-1.0f,-1.0f,1.0f };



	vertexData_[18].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[19].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData_[20].position = { -1.0f,-1.0f,-1.0f,1.0f };



	vertexData_[21].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData_[22].position = { -1.0f,-1.0f,-1.0f,1.0f };
	vertexData_[23].position = { 1.0f,-1.0f,-1.0f,1.0f };


	////上面。
	//vertexData_[16].position = { 1.0f,1.0f,1.0f,1.0f };
	//vertexData_[17].position = { -1.0f,1.0f,1.0f,1.0f };
	//vertexData_[18].position = { 1.0f,1.0f,-1.0f,1.0f };
	//vertexData_[19].position = { -1.0f,1.0f,-1.0f,1.0f };



	vertexData_[24].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[25].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData_[26].position = { -1.0f,1.0f,-1.0f,1.0f };



	vertexData_[27].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData_[28].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData_[29].position = { 1.0f,1.0f,-1.0f,1.0f };



	////下面。
	//vertexData_[20].position = { 1.0f,-1.0f,-1.0f,1.0f };
	//vertexData_[21].position = { -1.0f,-1.0f,-1.0f,1.0f };
	//vertexData_[22].position = { 1.0f,-1.0f,1.0f,1.0f };
	//vertexData_[23].position = { -1.0f,-1.0f,1.0f,1.0f };


	vertexData_[30].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[31].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData_[32].position = { 1.0f,-1.0f,-1.0f,1.0f };



	vertexData_[33].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData_[34].position = { 1.0f,-1.0f,-1.0f,1.0f };
	vertexData_[35].position = { -1.0f,-1.0f,-1.0f,1.0f };

	vertexResource_->Unmap(0, nullptr);

	materialResource_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(SkyBoxMaterial));

	textureHandle_ = textureHandle;
}

void SkyBox::Draw(WorldTransform& worldTransform, Camera& camera) 
{
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color = { 1.0f,1.0f,1.0f,1.0f };
	materialData_->uvTransform = MakeIdentity4x4();
	materialResource_->Unmap(0, nullptr);

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootSignature(PipelineManager::GetInstance()->GetSkyBoxRootSignature().Get());
	DirectXCommon::GetInstance()->GetCommandList()->SetPipelineState(PipelineManager::GetInstance()->GetSkyBoxGraphicsPipelineState().Get());

	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSphere_);

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, worldTransform.bufferResource_->GetGPUVirtualAddress());
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, camera.bufferResource_->GetGPUVirtualAddress());

	if (textureHandle_ != 0) 
	{
		TextureManager::GetInstance()->GraphicsCommand(textureHandle_);
	}

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(3, materialResource_->GetGPUVirtualAddress());

	DirectXCommon::GetInstance()->GetCommandList()->DrawInstanced(SURFACE_VERTEX_ * SURFACE_AMOUNT, 1, 0, 0);
}