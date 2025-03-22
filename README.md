# YTEngine - DirectX 12 ゲームエンジン
![Image](https://github.com/user-attachments/assets/a53e5925-b255-4041-9613-d5913088aaed)

## 各リポジトリの動作状態
- **マスターブランチ**
  - [![DebugBuild](https://github.com/JMacfield/YTEngine/actions/workflows/DebugBuild.yml/badge.svg)](https://github.com/JMacfield/YTEngine/actions/workflows/DebugBuild.yml)  
  - [![ReleaseBuild](https://github.com/JMacfield/YTEngine/actions/workflows/ReleaseBuild.yml/badge.svg)](https://github.com/JMacfield/YTEngine/actions/workflows/ReleaseBuild.yml)

## YTEngineとは?
**YTEngine** は、DirectX 12 を使用して開発中のゲームエンジンです。  
2023年4月から現在まで、約22カ月にわたり制作を続けています。

## YTEngineが目指す終着点
本エンジンおよびライブラリは、開発者本人だけでなく、誰でも簡単に利用できることを目指して設計しています。
ゲームエンジンやネットワークプログラミングに詳しくなくとも、スムーズに導入・活用できるよう工夫しています。

## 特徴
YTEngine には、以下のような機能が搭載されています。

- **グラフィックス**
  - グラフィックパイプライン PC用のDirectX12を使用して構築

- **ネットワーク機能**（WinSock2 を利用）
  - TCP/UDP 通信
  - データの同期
  - ノンブロッキング I/O

## 動作環境
| 必要環境 | 詳細 |
|----------|------|
| **DirectX** | DirectX 12 の動作が可能な環境 |
| **OS** | Windows 10 (20H2 以上) または Windows 11 |
| **Windows SDK** | 10.0.22621.0 以上 |
| **C++** | C++20 |

## 外部ライブラリ
- [assimp](https://github.com/assimp/assimp) （モデル読み込み）
- [DirectXTex](https://github.com/microsoft/DirectXTex) （テクスチャ処理）
- [imgui](https://github.com/ocornut/imgui) （GUI）
- [nlohmann/json](https://github.com/nlohmann/json) （JSON処理）

---

# YNet - ネットワークシステム

## YNet とは？
YNet は、YTEngine の開発と同時に制作している、WinSock2を利用したネットワーク通信システムです。  
ライブラリを作った本人でなくても使用できる構造分離を目指して開発しています。  
TCP・UDP の通信をサポートし、ゲーム内でのプレイヤー間の同期やサーバー通信を簡単に実装できます。  

### ネットワークディレクトリの構成
[ネットワークディレクトリ](https://github.com/JMacfield/YTEngine/tree/UnravelMaster/Network) には、YNet のコアに必要な全ファイルが含まれています。

## YNet の導入方法
### Windows（Visual Studio 2022 以降）
1. [YNet のソースコード](https://github.com/JMacfield/YNet_NetworkSystem) をダウンロード
2. `.sln`（ソリューションファイル）と同じ階層に配置
3. `Network/YNet/IncludeMe.h` をプロジェクト内でインクルード

```cpp
#include "Network/YNet/IncludeMe.h"
```

## YNet の基本的な使い方

### **1. 初期化**
ネットワークシステムを初期化するための関数です。

```cpp
bool NetworkManager::Initialize()
{
    if (!YNet::Network::Initialize())
    {
        std::cerr << "Failed to initialize network system." << std::endl;
        return false;
    }
    return true;
}
```

> `Initialize()` はエンジンの初期化処理の一部として組み込んでください。

---

### **2. 解放（シャットダウン）**
ネットワークシステムを適切に終了するための関数です。

```cpp
void NetworkManager::Shutdown()
{
    isRunning = false;

    if (receiveThread.joinable())
    {
        receiveThread.join();
    }

    if (connection)
    {
        connection->Close();
        delete connection;
        connection = nullptr;
    }

    YNet::Network::Shutdown();
}
```

> `Shutdown()` はエンジンの終了処理として組み込んでください。

---

### **3. 更新処理（Update 関数）**
ネットワーク通信のデータを処理する関数です。エンジンのメインループやゲームシーンの更新処理に組み込むことで、受信したデータを適切に処理できます。

```cpp
void NetworkManager::Update()
{
    std::lock_guard<std::mutex> lock(receiveMutex);
    while (!receiveQueue.empty())
    {
        auto data = std::move(receiveQueue.front());
        receiveQueue.pop();

        if (dataCallback)
        {
            dataCallback(data);
        }
    }
}
```

> `Update()` はフレームごとに呼び出し、データの処理を行うようにしてください。

---

### **4. クライアントの接続（Connect 関数）**
特定の IP アドレス・ポートに接続するための関数です。

```cpp
bool NetworkManager::Connect(const std::string& ip, uint16_t port)
{
    const char* cstr = ip.c_str();

    YNet::IPEndpoint endpoint(cstr, port);

    YNet::Socket socket;
    if (!socket.Create())
    {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    if (!socket.Connect(endpoint))
    {
        std::cerr << "Failed to connect to server: " << endpoint.ToString() << std::endl;
        return false;
    }

    connection = new YNet::TCPConnection(std::move(socket), endpoint);
    isRunning = true;
    receiveThread = std::thread(&NetworkManager::ReceiveLoop, this);

    return true;
}
```

> `Connect()` を使用して、クライアントからサーバーへ接続します。

---

### **5. データ受信処理（ReceiveLoop 関数）**
サーバーとの接続を維持しながら、データの受信を行うスレッドループです。

```cpp
void NetworkManager::ReceiveLoop()
{
    while (isRunning)
    {
        char buffer[1024];
        int bytesReceived = connection->socket.RecvAll(buffer, sizeof(buffer));

        if (bytesReceived > 0)
        {
            std::lock_guard<std::mutex> lock(receiveMutex);
            receiveQueue.push(std::vector<char>(buffer, buffer + bytesReceived));
        }
        else if (bytesReceived == 0)
        {
            std::cerr << "Server closed the connection." << std::endl;
            isRunning = false;
        }
        else
        {
            std::cerr << "Error while receiving data." << std::endl;
            isRunning = false;
        }
    }
}
```

---

### **6. 受信コールバックの設定（SetReceiveCallback 関数）**
受信データを処理するコールバック関数を設定できます。

```cpp
void NetworkManager::SetReceiveCallback(DataCallback callback)
{
    std::lock_guard<std::mutex> lock(receiveMutex);
    dataCallback = callback;
}
```

> 受信したデータを処理する関数を登録できます。

---

