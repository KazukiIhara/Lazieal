// This
#include "Object3dSystem.h"

// MyHedder
#include "DirectXCommon.h"
#include "PipelineManager.h"

cObject3dSystem::cObject3dSystem() {
}

cObject3dSystem::~cObject3dSystem() {
}

void cObject3dSystem::PreDraw() {
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	directX_->GetCommandList()->SetGraphicsRootSignature(pipelineManager_->GetRootSignature(cPipelineManager::kObject3d));
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	directX_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
