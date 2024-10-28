#pragma once

#include "YNet/SocketHandle.h"
#include "YNet/YResult.h"
#include "YNet/IPVersion.h"
#include "YNet/SocketOption.h"
#include "YNet/IPEndpoint.h"
#include "YNet/Constants.h"
#include "YNet/Packet.h"

namespace YNet 
{
	class Socket 
	{

	public:

		/// <summary>
		/// ソケットの初期化
		/// </summary>
		Socket(IPVersion ipversion = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);
		
		/// <summary>
		/// ソケットの作成
		/// </summary>
		YResult Create();

		/// <summary>
		/// ソケットを閉じる
		/// </summary>
		YResult Close();
		
		/// <summary>
		/// ソケットにIPをバインド
		/// </summary>
		/// <param name="endpoint">IPアドレス</param>
		YResult Bind(IPEndpoint endpoint);

		/// <summary>
		/// ソケットを受信待機状態にする
		/// </summary>
		/// <param name="endpoint">IPアドレス</param>
		/// <param name="backlog">ログ用int</param>
		YResult Listen(IPEndpoint endpoint, int backlog = 5);
		
		/// <summary>
		/// ソケットを接続
		/// </summary>
		/// <param name="outSocket">接続先ソケット</param>
		/// <param name="endpoint">IDアドレス</param>
		/// <returns></returns>
		YResult Accept(Socket& outSocket, IPEndpoint* endpoint = nullptr);
		
		/// <summary>
		/// 通信を接続
		/// </summary>
		/// <param name="endpoint">IDアドレス</param>
		YResult Connect(IPEndpoint endpoint);
		
		/// <summary>
		/// バッファを送信
		/// </summary>
		/// <param name="data">バッファ</param>
		/// <param name="numberOfBytes">バッファ番号</param>
		/// <param name="bytesSent">送信したパケット数</param>
		YResult Send(const void* data, int numberOfBytes, int& bytesSent);
		
		/// <summary>
		/// バッファを受信
		/// </summary>
		/// <param name="destination">受信元</param>
		/// <param name="numberOfBytes">バッファ番号</param>
		/// <param name="bytesReceived">受信したパケット数</param>
		YResult Recv(void* destination, int numberOfBytes, int& bytesReceived);
		
		/// <summary>
		/// バッファを全て送信
		/// </summary>
		/// <param name="data">バッファ</param>
		/// <param name="numberOfBytes">バッファ番号</param>
		YResult SendAll(const void* data, int numberOfBytes);
		
		/// <summary>
		/// バッファを全て受信
		/// </summary>
		/// <param name="destination">受信元</param>
		/// <param name="numberOfBytes">バッファ番号</param>
		/// <returns></returns>
		YResult RecvAll(void* destination, int numberOfBytes);
		
		/// <summary>
		/// パケットを送信
		/// </summary>
		/// <param name="packet">パケット</param>
		YResult Send(Packet& packet);
		
		/// <summary>
		/// パケットを受信
		/// </summary>
		/// <param name="packet">パケット</param>
		YResult Recv(Packet& packet);
		
		/// <summary>
		/// ハンドルの取得
		/// </summary>
		SocketHandle GetHandle();

		/// <summary>
		/// IPアドレスのバージョン取得
		/// </summary>
		/// <returns></returns>
		IPVersion GetIPVersion();
		
		/// <summary>
		/// ネットブロックの状態設定
		/// </summary>
		/// <param name="isBlocking">ブロックするかしないか</param>
		YResult SetBlocking(bool isBlocking);

	private:

		/// <summary>
		/// ソケットの設定
		/// </summary>
		/// <param name="option">ソケットオプション</param>
		/// <param name="value">番号</param>
		YResult SetSocketOption(SocketOption option, BOOL value);

		IPVersion ipversion = IPVersion::IPv4;
		
		SocketHandle handle = INVALID_SOCKET;
	};
}