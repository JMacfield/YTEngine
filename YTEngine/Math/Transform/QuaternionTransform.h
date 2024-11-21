/// クオータニオントランスフォーム

#pragma once

#include <Vector3.h>
#include <Quaternion.h>

namespace YTEngine
{
	/// <summary>
	/// クオータニオントランスフォーム
	/// </summary>
	struct QuaternionTransform {
		Vector3 scale;
		Quaternion rotate;
		Vector3 translate;
	};
}