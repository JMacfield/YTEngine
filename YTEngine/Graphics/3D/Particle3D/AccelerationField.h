/// 加速場について

#pragma once
#include <Vector3.h>
#include <AABB.h>

namespace YTEngine
{
	struct AccelerationField {
		Vector3 acceleration;
		AABB area;
	};
}