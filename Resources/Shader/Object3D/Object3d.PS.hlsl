#include "Object3d.hlsli"

struct Material 
{
	float4 color;
	int enableLighting;
	float4x4 uvTransform;
    float shininess;
};

struct DirectionalLight 
{
	float4 color;
	float3 direction;
	float intensity;
};

struct PointLight
{
	float4 color;
	float3 position;
	float intensity;
	float radius;
	float decay;
};

struct Camera
	{
    float3 worldPosition;
};

struct SpotLight
{
	float4 color;
	float3 position;
	float intensity;
	float3 direction;
	float distance;
	float decay;
	float cosFallowoffStart;
	float cosAngle;
};

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);
ConstantBuffer<Camera> gCamera : register(b2);
ConstantBuffer<PointLight> gPointLight : register(b3);
ConstantBuffer<SpotLight> gSpotLight : register(b4);

struct PixelShaderOutput 
{
	float4 color : SV_TARGET0;
};
 
PixelShaderOutput main(VertexShaderOutput input) 
{
	PixelShaderOutput output;
	
    float3 camera = gCamera.worldPosition;
	
	float4 transformedUV = mul(float4(input.texcoord,0.0f, 1.0f), gMaterial.uvTransform);
	float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    if (textureColor.a <= 0.5f)
	{
        discard;
    }
	
	if (gMaterial.enableLighting == 1)
	{
		float NdotL = dot(normalize(input.normal), -normalize(gDirectionalLight.direction));
		float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);

		float3 toEye = normalize(gCamera.worldPosition-input.worldPosition );
		
		float3 reflectLight = reflect(normalize(gDirectionalLight.direction), normalize(input.normal));
		
		float3 halfVector = normalize(-gDirectionalLight.direction + toEye);
        float NDotH = dot(normalize(input.normal), halfVector);
        float specularPow = pow(saturate(NDotH), gMaterial.shininess);
		
		float3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
		float3 specular = gDirectionalLight.color.rgb * gDirectionalLight.intensity * specularPow * float3(1.0f, 1.0f, 1.0f);
		
        if (textureColor.a <= 0.5f)
        {
            discard;
        }
		
		output.color.rgb = diffuse + specular;
        output.color.a = gMaterial.color.a * textureColor.a;
	}
	else if(gMaterial.enableLighting == 2)
	{
		float32_t3 pointLightDirection = normalize(input.worldPosition - gPointLight.position);
		
		float32_t NdotL = dot(normalize(input.normal), -pointLightDirection);
        float32_t cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
		
		float32_t3 toEye = normalize(gCamera.worldPosition - normalize(input.worldPosition));
		
		float32_t3 reflectLight = reflect(gPointLight.position, normalize(input.normal));
		
		float32_t distance = length(gPointLight.position - input.worldPosition);
		
		float32_t factor = pow(saturate(-distance / gPointLight.radius + 1.0f), gPointLight.decay);
		
		float32_t3 halfVector = normalize(-gPointLight.position + toEye);
        float NDotH = dot(normalize(input.normal), halfVector);
        float specularPow = pow(saturate(NDotH), gMaterial.shininess);
		
        float32_t3 diffusePointLight = gMaterial.color.rgb * textureColor.rgb * gPointLight.color.rgb * cos * gPointLight.intensity;
        float32_t3 specularPointLight = gPointLight.color.rgb * gPointLight.intensity * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
		
        if (textureColor.a <= 0.5f)
        {
            discard;
        }
      
		output.color.rgb = (diffusePointLight + specularPointLight) * factor;
        output.color.a = gMaterial.color.a * textureColor.a;
    }
	else if (gMaterial.enableLighting == 3)
	{
		float32_t3 spotLightDirectionOnSurface = normalize(input.worldPosition - gSpotLight.position);
		
		float32_t NdotL = dot(normalize(input.normal), -spotLightDirectionOnSurface);
        float32_t cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
		
		float32_t3 toEye = normalize(gCamera.worldPosition - normalize(input.worldPosition));
		
		float32_t3 reflectLight = reflect(gSpotLight.position, normalize(input.normal));
		
		float32_t distance = length(gSpotLight.position - input.worldPosition);
		
		float32_t attenuationFactor = pow(saturate(-distance / gSpotLight.distance + 1.0f), gSpotLight.decay);
		
		float32_t3 halfVector = normalize(-gSpotLight.position + toEye);
        float NDotH = dot(normalize(input.normal), halfVector);
        float specularPow = pow(saturate(NDotH), gMaterial.shininess);
		
		float32_t cosAngle = dot(spotLightDirectionOnSurface, gSpotLight.direction);
        float32_t falloffFactor = saturate((cosAngle - gSpotLight.cosAngle) / (gSpotLight.cosFallowoffStart - gSpotLight.cosAngle));
		
        float32_t3 diffuseSpotLight = gMaterial.color.rgb * textureColor.rgb * gSpotLight.color.rgb * cos * gSpotLight.intensity;
        float32_t3 specularSpotLight = gSpotLight.color.rgb * gSpotLight.intensity * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
		
        if (textureColor.a <= 0.5f)
        {
            discard;
        }
		
        output.color.rgb = (diffuseSpotLight + specularSpotLight) * attenuationFactor * falloffFactor;
        output.color.a = gMaterial.color.a * textureColor.a;
    }
    else
	{
		output.color = gMaterial.color * textureColor;
    }

	return output;
}