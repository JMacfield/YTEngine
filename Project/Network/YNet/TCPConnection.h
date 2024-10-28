#pragma once

#include "YNet/Socket.h"

namespace YNet 
{
	class TCPConnection 
	{

	public:

		/// <summary>
		/// TCP接続
		/// </summary>
		/// <param name="socket">接続先ソケット</param>
		/// <param name="endpoint">接続先IP</param>
		TCPConnection(Socket socket, IPEndpoint endpoint);

		/// <summary>
		/// TCP接続を終了
		/// </summary>
		void Close();
		
		/// <summary>
		/// IPアドレス変換
		/// </summary>
		std::string ToString();
		
		// ソケット
		Socket socket;

	private:

		// IPの終端
		IPEndpoint endpoint;

		// 変換後のIPアドレス
		std::string stringRepresentation = "";
	};
}