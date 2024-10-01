#pragma once

#include <DirectXMath.h>
#include <vector>
#include <WorldTransform.h>

// DrawLineクラス
class DrawLine {
public:
    DrawLine();
    ~DrawLine();

    // マウスがクリックされた時の開始点
    void StartLine(const DirectX::XMFLOAT2& startPos);

    // マウスが移動した際に描画する線を追加
    void AddPoint(const DirectX::XMFLOAT2& point);

    // 描画処理
    void Draw(const WorldTransform& transform);

    // マウスクリックを解除された際の処理
    void EndLine();

private:
    std::vector<DirectX::XMFLOAT2> points_; // 描画するポイントリスト
    bool isDrawing_; // 現在描画中かどうか
};
