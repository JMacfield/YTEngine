/// トランスフォーム

#pragma once

#include "Vector3.h"

namespace YTEngine
{
	/// <summary>
	/// トランスフォーム
	/// </summary>
	struct Transform {
		Vector3 scale;
		Vector3 rotate;
		Vector3 translate;
	};
}