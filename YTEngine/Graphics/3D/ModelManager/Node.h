/// ノードの宣言

#pragma once
#include <Matrix4x4.h>
#include <string>
#include <vector>
#include <QuaternionTransform.h>

namespace YTEngine
{
	struct Node {
		QuaternionTransform transform;
		Matrix4x4 localMatrix;
		std::string name;
		std::vector<Node> children;
	};
}