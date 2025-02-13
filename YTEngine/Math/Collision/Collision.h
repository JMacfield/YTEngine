#pragma once

#include "AABB.h"
#include "OBB.h"

#include "VectorCalculation.h"
#include "Matrix4x4Calculation.h"

#include "Matrix4x4.h"

/// 当たり判定クラス

#include <array>
#include <algorithm>
#include <cmath>
#include <vector>

/// <summary>
/// AABBと点の当たり判定
/// </summary>
bool IsCollisionAABBAndPoint(const AABB& aabb, const Vector3& point);

/// <summary>
/// OBBとOBBの当たり判定
/// </summary>
/// <param name="obb1">OBB1</param>
/// <param name="obb2">OBB2</param>
/// <returns></returns>
bool IsCollision(const OBB& obb1, const OBB& obb2);

bool TestAxis(const Vector3& axis, const OBB& obb1, const OBB& obb2);

std::pair<float, float> OBBProjection(const OBB& obb, const Vector3& axis);

bool ProjectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2);

// 回転軸の取得
Vector3 GetXAxis(const Matrix4x4& m);

Vector3 GetYAxis(const Matrix4x4& m);

Vector3 GetZAxis(const Matrix4x4& m);

void GetOrientations(const Matrix4x4& m, Vector3 orientations[3]);

bool SeparationAxis(const Vector3 axis, const OBB obb_1, const OBB obb_2);

void OBBIndex(const OBB& obb, std::vector<Vector3>& output_vertices);

// 回転軸のセット
Matrix4x4 SetRotate(const Vector3(&array)[3]);

// 当たり判定のトランスフォーム
Vector3 ColliTransform(const Vector3& vector, const Matrix4x4& matrix);