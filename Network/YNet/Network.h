#pragma once

#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace YNet 
{
	class Network 
	{

	public:

		static bool Initialize();
		static void Shutdown();
	};
}