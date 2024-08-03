// This
#include "Camera.h"

// C++
#include <cassert>

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "WinAPI.h"

void cCamera::Initialize(cWorldTransform* transform) {
	assert(transform);

	transform_ = transform;
	worldMatrix_ = MakeAffineMatrix(transform_->scale, transform_->rotate, transform_->translate);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(cWinAPI::kClientWidth) / float(cWinAPI::kClientHeight), 0.1f, 100.0f);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);
}

void cCamera::Update() {

	worldMatrix_ = MakeAffineMatrix(transform_->scale, transform_->rotate, transform_->translate);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_, aspectRaito_, nearClipRange_, farClipRange_);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);
}
