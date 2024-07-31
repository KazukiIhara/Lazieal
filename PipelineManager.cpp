#include "PipelineManager.h"

// DirectX
#pragma comment(lib,"dxcompiler.lib")

cPipelineManager::cPipelineManager() {
}

cPipelineManager::~cPipelineManager() {
}

ID3D12PipelineState* cPipelineManager::GetObject3DPipelineState(ePipelineState pipelineState, eBlendMode blendMode) {
	return graphicsPipelineState_[pipelineState][blendMode].Get();
}
