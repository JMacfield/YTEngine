#pragma once

#include "Network.h"
#include "TCPConnection.h"
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>

namespace YTEngine
{
    class NetworkManager
    {
    public:
        using DataCallback = std::function<void(const std::vector<char>&)>;

        NetworkManager();
        ~NetworkManager();

        /// <summary>
        /// 初期化
        /// </summary>
        /// <returns>初期化が正常に行われたか</returns>
        bool Initialize();

        /// <summary>
        /// 接続を解除・削除
        /// </summary>
        void Shutdown();

        /// <summary>
        /// 接続処理
        /// </summary>
        /// <param name="ip">IPアドレス</param>
        /// <param name="port">ポート番号</param>
        /// <returns>接続結果の可否</returns>
        bool Connect(const std::string& ip, uint16_t port);

        /// <summary>
        /// 送信
        /// </summary>
        /// <param name="data">任意のデータ</param>
        void Send(const std::vector<char>& data);

        /// <summary>
        /// コールバックセット
        /// </summary>
        /// <param name="callback"></param>
        void SetReceiveCallback(DataCallback callback);

        /// <summary>
        /// 更新
        /// </summary>
        void Update();

    private:
        void ReceiveLoop();

        YNet::TCPConnection* connection;
        std::thread receiveThread;
        std::mutex receiveMutex;
        std::queue<std::vector<char>> receiveQueue;
        DataCallback dataCallback;
        bool isRunning;
    };
}