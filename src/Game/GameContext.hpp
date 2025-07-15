#pragma once

#include <Essentials/Random.hpp>
#include <Game/Map.hpp>
#include <Game/UnitManager.hpp>
#include <IO/System/EventLog.hpp>
#include <cstdint>

namespace sw
{
	struct GameContext
	{
		Map& map;
		UnitManager& unitManager;
		Random& random;
		uint32_t& tick;
		EventLog& logger;
	};
}
