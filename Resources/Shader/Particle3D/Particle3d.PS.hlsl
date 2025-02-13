#include "Particle3d.hlsli"


struct Material
{
    float32_t4 color;
    int32_t enableLighting; ///
    float32_t4x4 uvTransform;
};


struct DirectionalLight
{
	//ライトの色
    float32_t4 color;
	//ライトの向き
    float32_t3 direction;
	//ライトの輝度
    float intensity;
};


ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);


struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};



 
PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
	
	//Materialを拡張する
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    output.color = gMaterial.color * textureColor*input.color;
    if (output.color.a == 0.0f)
    {
        discard;
    }
    
    
	////2値抜き
	////textureのα値が0.5以下の時にPixelを棄却
    //if (textureColor.a <= 0.5f)
    //{
    //    discard;
    //}
	
	
  
	
	
    return output;
}