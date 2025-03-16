# マスターディレクトリの動作状況

[![DebugBuild](https://github.com/JMacfield/YTEngine/actions/workflows/DebugBuild.yml/badge.svg)](https://github.com/JMacfield/YTEngine/actions/workflows/DebugBuild.yml)
[![ReleaseBuild](https://github.com/JMacfield/YTEngine/actions/workflows/ReleaseBuild.yml/badge.svg)](https://github.com/JMacfield/YTEngine/actions/workflows/ReleaseBuild.yml)


# YTEngine
### 概要
2023年4月～今現在までの約22カ月の間


制作しているDirectX12APIを使ったゲームエンジンです。
### 特徴
WinSock2を利用したネットワーククラス・ネットワークマネージャー


TCP/UDP通信・同期・ノンブロッキングI/O  
といった通信に関する様々な機能があります。

### 動作環境
* DirectX12の動作が可能な環境
* Windows SDK 10.0.22621.0 よりも高バージョン
* Windows 10 最低バージョン : 20H2 (私のPCはWindows 11ですが、10でも動作を確認済みです)
* C++ バージョン : 20

### 外部ライブラリ
* [assimp](https://github.com/assimp/assimp)  
* [DirectXTex](https://github.com/microsoft/DirectXTex)  
* [imgui](https://github.com/ocornut/imgui)
* [nlohmanjson](https://github.com/nlohmann/json)  

# YNet
### YNetに関する注意
[ネットワークディレクトリ](https://github.com/JMacfield/YTEngine/tree/UnravelMaster/Network)には  
YNetのコアに必要な全てのファイルが含まれています。  
プログラムでソースを作成する場合などに使用します。


### 導入方法
* Windowsユーザー (Visual Studio 2022 もしくはそれ以降のバージョン)  
[ネットワークソース](https://github.com/JMacfield/YNet_NetworkSystem)よりソースをダウンロードし、  
.slnと同階層へ配置後、Network/YNet/IncludeMe.hをインクルードしてください。

### ソースへの導入
```
 bool NetworkManager::Initialize()
    {
        if (!YNet::Network::Initialize())
        {
            std::cerr << "Failed to initialize network system." << std::endl;
            return false;
        }
        return true;
    }

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
1. Network/NetworkManager.h内にあるInitializeとShutdownは対になっています。  
2. Initializeはエンジン部の初期化へ　Shutdownはエンジン部の解放へ導入してください


※尚、ゲームシーン内に同じようにして導入することも可能です  


* Update関数は導入した場所（エンジン・ゲームシーン）の更新部へ差し込んでください  


* Connect関数は相手クライアント・サーバーへ接続することができます  
* ReceiveLoop関数は相手が閉じているか、更新されているかをキャッチすることができます  
* SetReceiveCallBack関数はコールバックをセットします  
