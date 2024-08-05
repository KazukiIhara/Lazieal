#include "Object3DUnUV.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<PunctualLight> gPunctualLight : register(b1);


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float32_t3 toEye = normalize(gPunctualLight.camera.worldPosition - input.worldPosition);
    
    // DirectionalLight    
    float32_t3 halfVector = normalize(-gPunctualLight.directionalLight.direction + toEye);
    float NDotH = dot(normalize(input.normal), halfVector);
    float specularPow = pow(saturate(NDotH), gMaterial.shininess);
    
    // PointLight
    float32_t3 pointLightDirection = normalize(input.worldPosition - gPunctualLight.pointLight.position);
    float32_t pointLightDistance = length(gPunctualLight.pointLight.position - input.worldPosition);
    float32_t pointLightFactor = pow(saturate(-pointLightDistance / gPunctualLight.pointLight.radius + 1.0), gPunctualLight.pointLight.decay);
    float32_t3 halfVectorPointLight = normalize(-pointLightDirection + toEye);
    float NDotHPoint = dot(normalize(input.normal), halfVectorPointLight);
    float specularPowPointLight = pow(saturate(NDotHPoint), gMaterial.shininess);
    
    // SpotLight
    float32_t3 spotLightDirectionOnSurface = normalize(input.worldPosition - gPunctualLight.spotLight.position);
    float32_t spotLightDistance = length(gPunctualLight.spotLight.position - input.worldPosition);
    float32_t spotLightAttenuationFactor = pow(saturate(-spotLightDistance / gPunctualLight.spotLight.distance + 1.0f), gPunctualLight.spotLight.decay);
    
    float32_t3 spotLightHalfVector = normalize(-spotLightDirectionOnSurface + toEye);
    float spotLightNDotH = dot(normalize(input.normal), spotLightHalfVector);
    float specularPowSpotLight = pow(saturate(spotLightNDotH), gMaterial.shininess);
    
    float32_t cosAngle = dot(spotLightDirectionOnSurface, gPunctualLight.spotLight.direction);
    float32_t falloffFactor = saturate((cosAngle - gPunctualLight.spotLight.cosAngle) / (gPunctualLight.spotLight.cosFalloffStart - gPunctualLight.spotLight.cosAngle));
    
    
    if (gMaterial.enbleLighting != 0)
    {
        // DirectionLight
        float nDotL = dot(normalize(input.normal), -gPunctualLight.directionalLight.direction);
        float cos = pow(nDotL * 0.5f + 0.5f, 2.0f);
        // PointLight
        float pointnDotL = dot(normalize(input.normal), -pointLightDirection);
        float cosPointLight = pow(pointnDotL * 0.5f + 0.5f, 2.0f);
        // SpotLight
        float spotLightnDotL = dot(normalize(input.normal), -spotLightDirectionOnSurface);
        float spotLightCos = pow(spotLightnDotL * 0.5f + 0.5f, 2.0f);
        
        // 拡散反射
        // DirectionalLight
        float32_t3 diffuseDirectionalLight =
        gMaterial.color.rgb * gPunctualLight.directionalLight.color.rgb * cos * gPunctualLight.directionalLight.intensity;
        // PointLight
        float32_t3 diffusePointLight =
        gMaterial.color.rgb *  gPunctualLight.pointLight.color.rgb * cosPointLight * gPunctualLight.pointLight.intensity * pointLightFactor;
        // SpotLight
        float32_t3 diffuseSpotLight =
        gMaterial.color.rgb *  gPunctualLight.spotLight.color.rgb * spotLightCos * gPunctualLight.spotLight.intensity * spotLightAttenuationFactor * falloffFactor;
        // 鏡面反射
        // DirectionalLight
        float32_t3 specularDirectionalLight = gPunctualLight.directionalLight.color.rgb * gPunctualLight.directionalLight.intensity * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
        // PointLight
        float32_t3 specularPointLight = gPunctualLight.pointLight.color.rgb * gPunctualLight.pointLight.intensity * pointLightFactor * specularPowPointLight * float32_t3(1.0f, 1.0f, 1.0f);
        // SpotLight
        float32_t3 specularSpotLight = gPunctualLight.spotLight.color.rgb * gPunctualLight.spotLight.intensity * spotLightAttenuationFactor * falloffFactor * specularPowSpotLight * float32_t3(1.0f, 1.0f, 1.0f);
        
        // 拡散反射、鏡面反射
        output.color.rgb = diffuseDirectionalLight + specularDirectionalLight + diffusePointLight + specularPointLight + diffuseSpotLight + specularSpotLight;
        

        // アルファ値は今まで通り
        output.color.a = gMaterial.color.a;
   
    }
    else
    {
        output.color = gMaterial.color;
    }
    
    // output.colorのa値が0の時にPixelを廃却
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}