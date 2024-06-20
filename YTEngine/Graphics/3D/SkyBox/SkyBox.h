#pragma once

#include "ConvertLog.h"
#include "DirectXCommon.h"
#include "DirectionalLight.h"
#include "Matrix4x4.h"
#include "Matrix4x4Calculation.h"
#include "Transform.h"
#include "TransformationMatrix.h"
#include "VertexData.h"

struct WorldTransform;
struct Camera;

class SkyBox
{
public:

	SkyBox() = default;
	~SkyBox() = default;

	void Create(uint32_t textureHandle);
	void Draw(WorldTransform& worldTransform, Camera& camera);

private:

	struct SkyBoxMaterial
	{
		Vector4 color;
		Matrix4x4 uvTransform;
	};

	enum VERTEX_POSITION
	{
		TOP_RIGHT_BACK,
		TOP_RIGHT_FRONT,
		BOTTOM_RIGHT_BACK,
		BOTTOM_RIGHT_FRONT,
	};

private:

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;
	VertexData* vertexData_ = nullptr;
	const int32_t SURFACE_VERTEX_ = 6;
	uint32_t SURFACE_AMOUNT = 6;

	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	uint32_t* indexData_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;
	SkyBoxMaterial* materialData_ = nullptr;

	uint32_t textureHandle_ = 0;
};