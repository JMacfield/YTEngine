#pragma once

#include <stdint.h>

namespace YNet 
{
	/// <summary>
	/// パケットタイプ
	/// </summary>
	enum PacketType : uint16_t 
	{
		PT_Invalid,
		PT_ChatMessage,
		PT_IntegerArray
	};
}