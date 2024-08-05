// This
#include "Object2dSystem.h"

// MyHedder
#include "DirectXCommon.h"
#include "PipelineManager.h"

cObject2DSystem::cObject2DSystem() {
}

cObject2DSystem::~cObject2DSystem() {
}

void cObject2DSystem::PreDraw() {
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	directX_->GetCommandList()->SetGraphicsRootSignature(pipelineManager_->GetRootSignature(cPipelineManager::kObject2d));
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	directX_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
