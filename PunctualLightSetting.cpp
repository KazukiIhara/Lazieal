#include "PunctualLightSetting.h"

cPunctualLightSetting::cPunctualLightSetting() {

}

cPunctualLightSetting::~cPunctualLightSetting() {

}

void cPunctualLightSetting::Initialize() {
	// DirectionalLightの初期化
	punctualLight.directionalLight.color = { 1.0f,1.0f,1.0f,1.0f };
	punctualLight.directionalLight.direction = { 0.0f,-1.0f,0.0f };
	punctualLight.directionalLight.intensity = 1.0f;

	// PointLightの初期化
	punctualLight.pointLight.color = { 1.0f,1.0f,1.0f,1.0f };
	punctualLight.pointLight.intensity = 0.0f;
	punctualLight.pointLight.position = { 0.0f,2.0f,7.0f };
	punctualLight.pointLight.radius = 10.0f;
	punctualLight.pointLight.decay = 5.0f;

	// SpotLightの初期化
	punctualLight.spotLight.color = { 1.0f,1.0f,1.0f,1.0f };
	punctualLight.spotLight.position = { 0.0f,2.0f,10.0f };
	punctualLight.spotLight.distance = 7.0f;
	punctualLight.spotLight.direction = Normalize({ 0.0f,-1.0f,0.0f });
	punctualLight.spotLight.intensity = 0.0f;
	punctualLight.spotLight.decay = 2.0f;
	punctualLight.spotLight.cosFalloffStart = 0.1f;
	punctualLight.spotLight.cosAngle = std::cos(std::numbers::pi_v<float> / 3.0f);

}
