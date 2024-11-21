/// 頂点の影響

#pragma once

#include <cstdint>
#include <array>

namespace YTEngine
{
	const uint32_t NUM_MAX_INFLUENCE = 4;
	struct VertexInfluence {
		std::array<float, NUM_MAX_INFLUENCE> weights;
		std::array<int32_t, NUM_MAX_INFLUENCE> jointIndices;
	};
}