#include "DrawSystem.h"
#include <d3d12.h>
#include <DirectXMath.h>

DrawLine::DrawLine() : isDrawing_(false) {}

DrawLine::~DrawLine() {}

void DrawLine::StartLine(const DirectX::XMFLOAT2& startPos) {
    points_.clear(); // 前のラインをリセット
    points_.push_back(startPos); // 新しい開始点を設定
    isDrawing_ = true;
}

void DrawLine::AddPoint(const DirectX::XMFLOAT2& point) {
    if (isDrawing_) {
        points_.push_back(point); // マウスが動くたびに新しい点を追加
    }
}

void DrawLine::Draw(const WorldTransform& transform) {
    if (points_.empty()) return;

    // DirectX12の描画コードはここに入ります
    // 例えば、以下は擬似的な頂点バッファの設定です

    // ... 頂点バッファのセットアップ処理

    // ラインを描画するループ処理
    for (size_t i = 1; i < points_.size(); ++i) {
        // 各ラインセグメントを描画
        // 実際のレンダリングコマンドはここに記述します
    }
}

void DrawLine::EndLine() {
    isDrawing_ = false;
}
