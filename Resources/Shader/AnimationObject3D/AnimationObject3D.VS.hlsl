#include "AnimationObject3D.hlsli"

struct TransformationMatrix 
{
	float4x4 world;
    float4x4 normal;
    float4x4 worldInverseTranspose;
};

struct Camera
{
	float4x4 viewMatrix_;
	float4x4 projectionMatrix_;
	float4x4 orthographicMatrix_;
};

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 weight : WEIGHT0;
    int4 index : INDEX0;
};

struct SkinningEnable
{
    int isSkinning;
};

struct Well
{
    float4x4 skeletonSpaceMatrix;
    float4x4 skeletonSpaceInverseTransposeMatrix;    
};

struct Skinned
{
    float4 position;
    float3 normal;
};

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<Camera> gCamera : register(b1);
StructuredBuffer<Well> gMatrixPalette : register(t0);

Skinned Skinning(VertexShaderInput input)
{
    Skinned skinned;
    
    skinned.position = mul(input.position, gMatrixPalette[input.index.x].skeletonSpaceMatrix) * input.weight.x;
    skinned.position += mul(input.position, gMatrixPalette[input.index.y].skeletonSpaceMatrix) * input.weight.y;
    skinned.position += mul(input.position, gMatrixPalette[input.index.z].skeletonSpaceMatrix) * input.weight.z;
    skinned.position += mul(input.position, gMatrixPalette[input.index.w].skeletonSpaceMatrix) * input.weight.w;
    skinned.position.w = 1.0f;
    
    skinned.normal = mul(input.normal, (float3x3) gMatrixPalette[input.index.x].skeletonSpaceInverseTransposeMatrix) * input.weight.x;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.y].skeletonSpaceInverseTransposeMatrix) * input.weight.y;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.z].skeletonSpaceInverseTransposeMatrix) * input.weight.z;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.w].skeletonSpaceInverseTransposeMatrix) * input.weight.w;
    skinned.normal = normalize(skinned.normal);
    
    return skinned;
}

VertexShaderOutput main(VertexShaderInput input) 
{
	VertexShaderOutput output;
	
    Skinned skinned = Skinning(input);
    
    float4x4 world = gTransformationMatrix.world;
    float4x4 viewProjection = mul(gCamera.viewMatrix_, gCamera.projectionMatrix_);
	
    float4x4 wvp = mul(world, viewProjection);
	
	output.position = mul(skinned.position, wvp);
    output.texcoord = input.texcoord;
	
    output.normal = normalize(mul(skinned.normal, (float3x3) gTransformationMatrix.worldInverseTranspose));
	
	output.worldPosition = mul(skinned.position, gTransformationMatrix.world).xyz;
    
    return output;
}