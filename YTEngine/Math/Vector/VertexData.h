/// 頂点データ

#pragma once
#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

namespace YTEngine
{
	/// <summary>
	/// 頂点データ
	/// </summary>
	struct VertexData {
		Vector4 position;
		Vector2 texCoord;
		Vector3 normal;
	};
}