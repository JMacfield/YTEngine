#include "HSVFilter.hlsli"

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

struct HSV
{
    float hue;
    float saturation;
    float value;
};

ConstantBuffer<HSV> gHSV : register(b0);

Texture2D<float4> gTexture : register(t0);
SamplerState gSample : register(s0);

//RGBからHSVへ
float3 RGBToHSV(float3 color){
    float red = color.r;
    float green = color.g;
    float blue = color.b;
    
    float max = red > green ? red : green;
    max = max > blue ? max : blue;
    float min = red < green ? red : green;
    min = min < blue ? min : blue;
    float h = max - min;
    if (h > 0.0f){
        if (max == red){
            h = (green - blue) / h;
            if (h < 0.0f){
                h += 6.0f;
            }
        }
        else if (max == green){
            h = 2.0f + (blue - red) / h;
        }
        else{
            h = 4.0f + (red - green) / h;
        }
    }
    h /= 6.0f;
    float s = (max - min);
    if (max != 0.0f){
        s /= max;
    }
        
    float value = max;
    float3 hsv = { h, s, value };
    
    
    return hsv;
}

//HSVからRGBへ
float3 HSVToRGB(float3 hsv)
{
    float red = hsv.z;
    float green = hsv.z;
    float blue = hsv.z;
    
    float h = hsv.x;
    float s = hsv.y;
    
    
    if (s > 0.0f){
        h *= 6.0f;
        int i = (int) h;
        float f = h - (float) i;
        switch (i){
            default:
            case 0:
                green *= 1 - s * (1 - f);
                blue *= 1 - s;
                break;
            case 1:
                red *= 1 - s * f;
                blue *= 1 - s;
                break;
            case 2:
                red *= 1 - s;
                blue *= 1 - s * (1 - f);
                break;
            case 3:
                red *= 1 - s;
                green *= 1 - s * f;
                break;
            case 4:
                red *= 1 - s * (1 - f);
                green *= 1 - s;
                break;
            case 5:
                green *= 1 - s;
                blue *= 1 - s * f;
                break;
        }
    }
    
    float3 rgb = { red,green,blue};
    return rgb;
}

float WrapValue(float value, float minRange, float maxRange)
{
    float range = maxRange - minRange;
    float modValue = fmod(value - minRange, range);
    if (modValue < 0)
    {
        modValue += range;
    }
    return minRange + modValue;
    
}



PixelShaderOutput main(VertexShaderOutput input){
    PixelShaderOutput output;
    
    float4 textureColor = gTexture.Sample(gSample, input.texcoord);
   
    float3 hsv = RGBToHSV(textureColor.rgb);
    
    
    hsv.x += gHSV.hue;
    hsv.y += gHSV.saturation;
    hsv.z += gHSV.value;
    
    
    hsv.x = WrapValue(hsv.x,0.0f,1.0f);
    hsv.y = saturate(hsv.y);
    hsv.z = saturate(hsv.z);
    
    
    float3 rgb = HSVToRGB(hsv);
    
    output.color.rgb = rgb;
    output.color.a = textureColor.a;
    
    return output;
}