#pragma once

#include <Game/GameContext.hpp>
#include <Game/UnitManager.hpp>
#include <cstdint>
#include <fstream>

namespace sw
{
	namespace io
	{
		struct CreateMap;
		struct SpawnSwordsman;
		struct SpawnHunter;
		struct March;
	}

	class EventLog;

	class Simulation
	{
	public:
		explicit Simulation(EventLog& eventLog, uint32_t randomSeed) :
				_eventLog(eventLog),
				_random(randomSeed)
		{}

		void process(std::ifstream& file);

	private:
		void handleCreateMap(const io::CreateMap& cmd);
		void handleSpawnSwordsman(const io::SpawnSwordsman& cmd);
		void handleSpawnHunter(const io::SpawnHunter& cmd);
		void handleMarch(const io::March& cmd);

		EventLog& _eventLog;
		UnitManager _unitManager{};
		std::unique_ptr<Map> _map{};
		uint32_t _tick{};
		Random _random;
	};
}
