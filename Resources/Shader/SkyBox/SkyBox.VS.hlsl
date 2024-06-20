#include "SkyBox.hlsli"

struct VertexShaderInput
{
    float4 position : POSITION0;
    float3 texcoord : TEXCOORD0;
};

struct TransformationMatrix
{
    float4x4 world;
};

struct Camera
{
    float4x4 viewMatrix_;
    float4x4 projectionMatrix_;
    float4x4 orthographicsMatrix_;
};

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<Camera> gCamera : register(b1);

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    float4x4 viewProjection = mul(gCamera.viewMatrix_, gCamera.projectionMatrix_);
    float4x4 wvp = mul(gTransformationMatrix.world, viewProjection);
    
    output.position = mul(input.position, wvp).xyzw;
    output.texcoord = input.position.xyz;
    
    return output;
}