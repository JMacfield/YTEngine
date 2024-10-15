/// 行列変換

#pragma once
#include "Matrix4x4.h"

/// <summary>
/// 行列変換
/// </summary>
struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};