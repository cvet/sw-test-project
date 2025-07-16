

#include <Game/Simulation.hpp>
#include <Game/Unit.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <cassert>
#include <cstdint>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace sw
{
	void Simulation::process(std::ifstream& file)
	{
		std::cout << "Starting simulation\n";

		_tick = 1;

		io::CommandParser parser;

		parser.add<io::CreateMap>([&](io::CreateMap cmd) { handleCreateMap(cmd); })
			.add<io::SpawnSwordsman>([&](io::SpawnSwordsman cmd) { handleSpawnSwordsman(cmd); })
			.add<io::SpawnHunter>([&](io::SpawnHunter cmd) { handleSpawnHunter(cmd); })
			.add<io::March>([&](io::March cmd) { handleMarch(cmd); });

		parser.parse(file);

		if (!_map)
		{
			throw std::runtime_error("Map not created");
		}

		GameContext ctx{
			.map = *_map, .unitManager = _unitManager, .random = _random, .tick = _tick, .logger = _eventLog};

		while (ctx.unitManager.hasActiveUnits())
		{
			if (_debugMode)
			{
				debugRender();
			}

			_tick++;

			auto units = ctx.unitManager.getUnits();

			for (const auto& unit : units)
			{
				unit->update(ctx);
			}

			for (const auto& unit : units)
			{
				if (auto health = unit->getComponent<HealthComponent>())
				{
					if (!health->isAlive())
					{
						ctx.logger.log(ctx.tick, io::UnitDied{.unitId = unit->getId()});

						ctx.map.removeUnit(unit);
						ctx.unitManager.removeUnit(unit);
					}
				}
			}
		}

		std::cout << "Simulation finished\n";

		if (_debugMode)
		{
			debugRender();
		}
	}

	void Simulation::handleCreateMap(const io::CreateMap& cmd)
	{
		if (_map)
		{
			throw std::runtime_error("Map already created");
		}

		_map = std::make_unique<Map>(cmd.width, cmd.height);

		_eventLog.log(_tick, io::MapCreated{.width = cmd.width, .height = cmd.height});
	}

	void Simulation::handleSpawnSwordsman(const io::SpawnSwordsman& cmd)
	{
		if (!_map)
		{
			throw std::runtime_error("Map not created before spawning units");
		}
		if (_unitManager.getUnitById(cmd.unitId))
		{
			throw std::runtime_error("Unit with ID " + std::to_string(cmd.unitId) + " already exists");
		}

		auto pos = pos_t{static_cast<int32_t>(cmd.x), static_cast<int32_t>(cmd.y)};
		auto hp = static_cast<int32_t>(cmd.hp);
		auto strength = static_cast<int32_t>(cmd.strength);
		auto unit = sw::UnitManager::createSwordsman(cmd.unitId, pos, hp, strength);

		_map->addUnit(unit);
		_unitManager.addUnit(unit);

		_eventLog.log(_tick, io::UnitSpawned{.unitId = cmd.unitId, .unitType = "Swordsman", .x = cmd.x, .y = cmd.y});
	}

	void Simulation::handleSpawnHunter(const io::SpawnHunter& cmd)
	{
		if (!_map)
		{
			throw std::runtime_error("Map not created before spawning units");
		}
		if (_unitManager.getUnitById(cmd.unitId))
		{
			throw std::runtime_error("Unit with ID " + std::to_string(cmd.unitId) + " already exists");
		}

		auto pos = pos_t{static_cast<int32_t>(cmd.x), static_cast<int32_t>(cmd.y)};
		auto hp = static_cast<int32_t>(cmd.hp);
		auto strength = static_cast<int32_t>(cmd.strength);
		auto agility = static_cast<int32_t>(cmd.agility);
		auto range = static_cast<int32_t>(cmd.range);
		auto unit = sw::UnitManager::createHunter(cmd.unitId, pos, hp, agility, strength, range);

		_map->addUnit(unit);
		_unitManager.addUnit(unit);

		_eventLog.log(_tick, io::UnitSpawned{.unitId = cmd.unitId, .unitType = "Hunter", .x = cmd.x, .y = cmd.y});
	}

	void Simulation::handleMarch(const io::March& cmd)
	{
		auto unit = _unitManager.getUnitById(cmd.unitId);

		if (!unit)
		{
			throw std::runtime_error("Unit not found: " + std::to_string(cmd.unitId));
		}

		auto movementComponent = unit->getComponent<MovementComponent>();

		if (!movementComponent)
		{
			throw std::runtime_error("Unit does not have a MovementComponent: " + std::to_string(cmd.unitId));
		}

		auto pos = pos_t{static_cast<int32_t>(cmd.targetX), static_cast<int32_t>(cmd.targetY)};
		movementComponent->setTarget(pos);

		const auto startPos = unit->getPosition();
		_eventLog.log(
			_tick,
			io::MarchStarted{
				.unitId = cmd.unitId,
				.x = static_cast<uint32_t>(startPos.x),
				.y = static_cast<uint32_t>(startPos.y),
				.targetX = cmd.targetX,
				.targetY = cmd.targetY});
	}

	void Simulation::debugRender() const
	{
		assert(_map && "Map must be created before rendering");
		const auto screenWidth = ftxui::Dimension::Fixed(_map->getWidth());
		const auto screenHeight = ftxui::Dimension::Fixed(_map->getHeight());
		auto screen = ftxui::Screen::Create(screenWidth, screenHeight);

		for (int32_t x = 0; x < _map->getWidth(); ++x)
		{
			for (int32_t y = 0; y < _map->getHeight(); ++y)
			{
				const auto& unit = _map->unitAtPos({x, y});
				auto& pixel = screen.PixelAt(x, y);

				pixel.character = U' ';
				pixel.foreground_color = ftxui::Color::Red;
				pixel.background_color = ftxui::Color::RGB(0, 255, 0);
				pixel.bold = true;

				if (unit)
				{
					pixel.character = unit->getId() > 9 ? U'X' : U'0' + unit->getId();
				}
			}
		}

		screen.Print();
		std::cout << "\nPress Enter to simulate turn...";
		std::cin.get();
		std::cout << screen.ResetPosition(true);
		std::cout << "\x1B[1A";
		std::cout << "\x1B[2K";
		std::cout << "\x1B[1A";
		std::cout << "\x1B[2K";
		std::cout << std::flush;
	}
}
