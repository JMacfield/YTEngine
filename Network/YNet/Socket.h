#pragma once

#include "SocketHandle.h"
#include "YResult.h"
#include "IPVersion.h"
#include "SocketOption.h"
#include "IPEndpoint.h"
#include "Constants.h"
#include "Packet.h"

namespace YNet 
{
	class Socket 
	{

	public:

		Socket(IPVersion ipversion = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);
		
		YResult Create();
		YResult Close();
		
		YResult Bind(IPEndpoint endpoint);
		YResult Listen(IPEndpoint endpoint, int backlog = 5);
		YResult Accept(Socket& outSocket, IPEndpoint* endpoint = nullptr);
		YResult Connect(IPEndpoint endpoint);
		YResult Send(const void* data, int numberOfBytes, int& bytesSent);
		YResult Recv(void* destination, int numberOfBytes, int& bytesReceived);
		YResult SendAll(const void* data, int numberOfBytes);
		YResult RecvAll(void* destination, int numberOfBytes);
		YResult Send(Packet& packet);
		YResult Recv(Packet& packet);
		
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
		
		YResult SetBlocking(bool isBlocking);

	private:
		YResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		
		SocketHandle handle = INVALID_SOCKET;
	};
}