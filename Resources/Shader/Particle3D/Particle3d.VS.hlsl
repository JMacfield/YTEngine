#include "Particle3d.hlsli"

struct ParticleForGPU
{
    float32_t4x4 World;
    float32_t4 color;
};

struct Camera
{
	float32_t4x4 viewMatrix_;
	float32_t4x4 projectionMatrix_;
	float32_t4x4 orthographicMatrix_;
};

StructuredBuffer<ParticleForGPU> gParticle : register(t0);
ConstantBuffer<Camera> gCamera : register(b1);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};


VertexShaderOutput main(VertexShaderInput input,uint32_t instanceId:SV_InstanceID)
{
    VertexShaderOutput output;
	
    float32_t4x4 viewProjection = mul(gCamera.viewMatrix_, gCamera.projectionMatrix_);
    float32_t4x4 wvp = mul(gParticle[instanceId].World, viewProjection);
    
    output.position = mul(input.position, wvp);
    output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float32_t3x3) gParticle[instanceId].World));
    output.color = gParticle[instanceId].color;
    
    return output;
}