#include "Object3d.hlsli"

struct TransformationMatrix 
{
	float4x4 world;
    float4x4 normal;
    float4x4 worldInverseTranspose;
};

struct Camera{
	float4x4 viewMatrix_;
	float4x4 projectionMatrix_;
	float4x4 orthographicMatrix_;
};


struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<Camera> gCamera : register(b1);

VertexShaderOutput main(VertexShaderInput input) 
{
	VertexShaderOutput output;
	
    float4x4 world = gTransformationMatrix.world;
    float4x4 viewProjection = mul(gCamera.viewMatrix_, gCamera.projectionMatrix_);
	
    float4x4 wvp = mul(world, viewProjection);
	
	output.position = mul(input.position, wvp);
    output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float3x3) gTransformationMatrix.worldInverseTranspose));
	
	output.worldPosition = mul(input.position, gTransformationMatrix.world).xyz;
   
    
    
    return output;
}