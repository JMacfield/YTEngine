#include "TextureManager.h"
#include "SrvManager.h"

static uint32_t descriptorSizeSRV_ = 0u;
static uint32_t descriptorSizeRTV_ = 0u;
static uint32_t descriptorSizeDSV_ = 0u;
static uint32_t textureIndex;

static DirectX::ScratchImage mipImages_[TextureManager::TEXTURE_MAX_AMOUNT_];
static D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc[TextureManager::TEXTURE_MAX_AMOUNT_];

TextureManager::TextureManager() 
{

}

TextureManager* TextureManager::GetInstance() 
{	
	static TextureManager instance;

	return &instance;
}

const D3D12_RESOURCE_DESC TextureManager::GetResourceDesc(uint32_t textureHandle) 
{
	//テクスチャの情報を取得
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc = textureInformation_[textureHandle].resource_->GetDesc();

	return resourceDesc;
}


void TextureManager::Initialize() 
{
	CoInitializeEx(0, COINIT_MULTITHREADED);

	descriptorSizeSRV_ =  DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	descriptorSizeRTV_ =  DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSizeDSV_ =  DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	
	textureIndex = 0;
}

uint32_t TextureManager::LoadTexture(const std::string& filePath) 
{
	for (int i = 0; i < TEXTURE_MAX_AMOUNT_; i++) 
	{
		//同じテクスチャがあった場合そのテクスチャハンドルを返す
		if (TextureManager::GetInstance()->textureInformation_[i].name_ == filePath) 
		{
			return TextureManager::GetInstance()->textureInformation_[i].handle_;
		}
	}

	textureIndex= SrvManager::GetInstance()->Allocate();


	//テクスチャの名前
	TextureManager::GetInstance()->textureInformation_[textureIndex].name_ = filePath;
	
	//テクスチャハンドル
	TextureManager::GetInstance()->textureInformation_[textureIndex].handle_ = textureIndex;

	//Textureを読んで転送する
	mipImages_[textureIndex] = LoadTextureData(filePath);

	const DirectX::TexMetadata& metadata = mipImages_[textureIndex].GetMetadata();

	TextureManager::GetInstance()->textureInformation_[textureIndex].resource_ = CreateTextureResource(metadata);
	UploadTextureData(TextureManager::GetInstance()->textureInformation_[textureIndex].resource_.Get(), mipImages_[textureIndex]);

	//SRVの確保
	TextureManager::GetInstance()->textureInformation_[textureIndex].handle_ = textureIndex;

	//SRVの生成
	SrvManager::GetInstance()->CreateSRVForTexture2D(
		TextureManager::GetInstance()->textureInformation_[textureIndex].handle_,
		TextureManager::GetInstance()->textureInformation_[textureIndex].resource_.Get(),
		metadata, UINT(metadata.mipLevels));

	return textureIndex;
}
	
//1.TextureデータそのものをCPUで読み込む
DirectX::ScratchImage TextureManager::LoadTextureData(const std::string& filePath) 
{	
	//テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr;

	if (filePathW.ends_with(L".dds"))
	{
		hr = DirectX::LoadFromDDSFile(filePathW.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
	}
	else
	{
		hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	}
	
	assert(SUCCEEDED(hr));
	
	//ミップマップの作成
	DirectX::ScratchImage mipImages{};
	
	if (DirectX::IsCompressed(image.GetMetadata().format))
	{
		mipImages = std::move(image);
	}
	else
	{
		hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 4, mipImages);
	}

	assert(SUCCEEDED(hr));

	return mipImages;
}

//2.DirectX12のTextureResourceを作る
ComPtr<ID3D12Resource> TextureManager::CreateTextureResource(const DirectX::TexMetadata& metadata) 
{
	ComPtr<ID3D12Resource> resource = nullptr;
	
	//1.metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	//Textureの幅
	resourceDesc.Width = UINT(metadata.width);
	//Textureの高さ
	resourceDesc.Height = UINT(metadata.height);
	//mipmapの数
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	//奥行き or 配列Textureの配列数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	//TextureのFormat
	resourceDesc.Format = metadata.format;
	//サンプリングカウント
	resourceDesc.SampleDesc.Count = 1;
	//Textureの次元数。普段使っているのは2次元
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	//2.利用するHeapの設定
	//利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	//細かい設定を行う
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	//WriteBackポリシーでCPUアクセス可能
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	//プロセッサの近くに配置
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	//3.Resourceを生成する
	HRESULT hr =  DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,					//Heapの設定
		D3D12_HEAP_FLAG_NONE,				//Heapの特殊な設定
		&resourceDesc,						//Resourceの設定
		D3D12_RESOURCE_STATE_COPY_DEST,	//初回のResourceState。データの転送を受け入れられるようにする
		nullptr,							//Clear最適値。使わないのでnullptr
		IID_PPV_ARGS(&resource));			//作成するResourceポインタへのポインタ

	assert(SUCCEEDED(hr));

	return resource;
}

[[nodiscard]]
ComPtr<ID3D12Resource> TextureManager::UploadTextureData(ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages) 
{
	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	DirectX::PrepareUpload(DirectXCommon::GetInstance()->GetDevice().Get(), mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermidiateSize = GetRequiredIntermediateSize(texture.Get(), 0, UINT(subresources.size()));
	ComPtr<ID3D12Resource> intermediateSizeResource = DirectXCommon::GetInstance()->CreateBufferResource(intermidiateSize);
	UpdateSubresources(DirectXCommon::GetInstance()->GetCommandList().Get(), texture.Get(), intermediateSizeResource.Get(), 0, 0, UINT(subresources.size()), subresources.data());

	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture.Get();
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;

	DirectXCommon::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrier);

	return intermediateSizeResource;
}

void TextureManager::GraphicsCommand(uint32_t texHandle) 
{
	SrvManager::GetInstance()->SetGraphicsRootDescriptorTable(2, texHandle);
}

void TextureManager::Release() 
{
	CoUninitialize();
}

TextureManager::~TextureManager() 
{

}