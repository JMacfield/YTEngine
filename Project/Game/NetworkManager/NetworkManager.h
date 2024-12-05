#define STRICT

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class NetworkManager
{
public:

	enum class Mode {
		None,
		Server,
		Client,
	};

	NetworkManager();
	~NetworkManager();

	/// <summary>
	/// サーバーとして起動する
	/// </summary>
	/// <param name="port">ポート番号</param>
	/// <returns></returns>
	bool StartServer(unsigned short port);

	/// <summary>
	/// クライアントとしてサーバーに接続
	/// </summary>
	/// <param name="ip"></param>
	/// <param name="port"></param>
	/// <returns></returns>
	bool ConnectToServer(const char* ip, unsigned short port);

	/// <summary>
	/// データ送信
	/// </summary>
	/// <param name="data">送る型</param>
	/// <param name="size">サイズ</param>
	/// <returns></returns>
	bool SendData(const void* data, int size);

	/// <summary>
	/// データ受信
	/// </summary>
	/// <param name="buffer">バッファ</param>
	/// <param name="size">サイズ</param>
	/// <returns></returns>
	bool ReceiveData(void* buffer, int size);

	/// <summary>
	/// 接続を閉じる
	/// </summary>
	void Close();

private:

	/// <summary>
	/// 接続を許可
	/// </summary>
	void AcceptConnections();

	Mode mode_;
	SOCKET socket_;
	std::vector<SOCKET> clients_;
	std::mutex clientMutex_;
	std::thread acceptThread_;
	bool isRunning_;
};