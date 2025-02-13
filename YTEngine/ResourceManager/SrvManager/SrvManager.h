// シェーダーリソースビューを管理するクラス

#pragma once

#include "DirectXCommon.h"

class SrvManager final
{
private:
	//コンストラクタ
	SrvManager() = default;

	//デストラクタ
	~SrvManager() = default;

public:
	//インスタンス
	static SrvManager* GetInstance();

	//コピーコンストラクタ禁止
	SrvManager(const SrvManager& srvHeapManager) = delete;

	//代入演算子を無効にする
	SrvManager& operator=(const SrvManager& rvHeapManager) = delete;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	// 許可
	uint32_t Allocate();

	/// <summary>
	/// 事前描画
	/// </summary>
	void PreDraw();

	// シェーダーリソースビューの作成
	void CreateSRVForTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevels);
	void CreateSRVForStructuredBuffer(uint32_t srvIndex, ID3D12Resource* pResource, UINT numElements, UINT structureByteStride);

	// グラフィックをディスクリプタテーブルへ
	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex);
	

public:

	// 各ディスクリプタを取得
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

	// シェーダーリソースビューのヒープを取得
	ComPtr<ID3D12DescriptorHeap> GetSrvDescriptorHeap() {
		return  descriptorHeap_;
	}

private:
	//最大SRV数(最大テクスチャ数)
	static const uint32_t MAX_SRV_COUNT_;

	//SRV用のデスクリプタサイズ
	uint32_t descriptorSize_ =  0;

	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descriptorHeap_=nullptr;

	//画像読み込み
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU_ = {};
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU_ = {};

	//次に使用するSRVインデックス
	uint32_t useIndex_ = 1;
	


};

