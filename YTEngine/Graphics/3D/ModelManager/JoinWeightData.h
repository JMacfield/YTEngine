/// ジョイントの重さ（影響）

#pragma once
#include <Matrix4x4.h>
#include <VertexWeightData.h>
#include <vector>

namespace YTEngine
{
	struct JointWeightData {
		Matrix4x4 inverseBindPoseMatrix;
		std::vector<VertexWeightData> vertexWeights;
	};
}