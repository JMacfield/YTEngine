/// ワールドトランスフォームを管理するクラス

#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"

#include "DirectXCommon.h"

namespace YTEngine
{
	// ワールドトランスフォームの構造体
	struct WorldTransformData {
		Matrix4x4 world;
		Matrix4x4 normal;
		Matrix4x4 worldInverseTranspose;
	};

	struct WorldTransform {
	public:
#pragma region メンバ関数

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 初期化 glTFを使う時
		/// </summary>
		void Initialize(bool isUseGLTF, Matrix4x4 matrix4x4);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 更新 行列を使う時
		/// </summary>
		/// <param name="animationLocalMatrix">行列</param>
		void Update(Matrix4x4 animationLocalMatrix);

		/// <summary>
		/// ペアレントの設定
		/// </summary>
		/// <param name="parent">ペアレントする物</param>
		void SetParent(const WorldTransform* parent) {
			parent = parent_;
		}

		//glTF用
		void  SetRootNodeLocalMatrix(Matrix4x4 matrix4x4) {
			this->rootNodeLocalMatrix_ = matrix4x4;
		}

		/// <summary>
		/// ワールドトランスフォームの取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetWorldPosition();

	private:

		/// <summary>
		/// 送信
		/// </summary>
		void Transfer();


#pragma endregion

#pragma region メンバ変数


	public:

		bool isUseGLTF_ = false;

		//スケール
		Vector3 scale_ = { 1.0f, 1.0f, 1.0f };
		//回転
		Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
		//座標
		Vector3 translate_ = { 0.0f, 0.0f, 0.0f };

		//glTFからローカル行列を受け取る
		Matrix4x4 rootNodeLocalMatrix_ = {};

		Matrix4x4 animationLocalMatrix_ = {};

		//定数バッファ
		ComPtr<ID3D12Resource> bufferResource_;

		WorldTransformData* tranceformationData_ = nullptr;

		//ワールド行列へ
		Matrix4x4 worldMatrix_ = {};
		//逆転置行列
		Matrix4x4 worldInverseTransposeMatrix_ = {};

		//親となるワールド変換へのポインタ
		const WorldTransform* parent_ = nullptr;

#pragma endregion

	};
}