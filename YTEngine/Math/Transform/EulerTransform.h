/// オイラー角トランスフォーム

#pragma once

#include <Vector3.h>

/// <summary>
/// オイラー角トランスフォーム
/// </summary>
struct EulerTransform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};
