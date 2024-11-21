/// 球体形状

#pragma once
#include "Vector3.h"

namespace YTEngine
{
	/// <summary>
	/// 球体形状構造体
	/// </summary>
	struct SphereShape {
		Vector3 center;
		float radius;
	};
}