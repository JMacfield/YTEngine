/// 光源の種類についてのクラス

#pragma once

namespace YTEngine
{
	/// <summary>
	/// 光源の種類の配列
	/// </summary>
	enum LightingType {
		None,
		Directional,
		Point,
		Spot,
	};
}