/// OBB形状

#pragma once

#include "Vector3.h"

namespace YTEngine
{
	/// <summary>
	/// OBB形状構造体
	/// </summary>
	struct OBB {
		Vector3 center;
		Vector3 orientation[3];
		Vector3 size;
	};
}