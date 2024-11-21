/// GPU計算用（スケルトン）

#pragma once
#include <Matrix4x4.h>

namespace YTEngine
{
	struct WellForGPU {
		//位置用
		Matrix4x4 skeletonSpaceMatrix;
		//法線用
		Matrix4x4 skeletonSpaceIncerseTransposeMatrix;
	};
}