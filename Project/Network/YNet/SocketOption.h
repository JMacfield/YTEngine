#pragma once

namespace YNet 
{
	/// <summary>
	/// IPバージョンの選択
	/// </summary>
	enum SocketOption 
	{
		TCP_NoDelay, // trueの時アルゴリズムを無効化
		IPV6_Only, // true IPv4 IPv6両方で接続可能
	};
}