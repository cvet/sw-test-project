#include <Game/UnitManager.hpp>
#include <cassert>

namespace sw
{
	void UnitManager::addUnit(const std::shared_ptr<Unit>& unit)
	{
		assert(std::ranges::find(_units, unit) == _units.end() && "Unit already exists in the units vector");
		assert(!_unitsMap.contains(unit->getId()) && "Unit already exists in the map");

		_units.emplace_back(unit);
		_unitsMap.emplace(unit->getId(), unit);
	}

	void UnitManager::removeUnit(const std::shared_ptr<Unit>& unit)
	{
		const auto it = std::ranges::find(_units, unit);
		assert(it != _units.end() && "Unit not found in the units vector");
		_units.erase(it);
		_unitsMap.erase(unit->getId());
	}

	std::shared_ptr<Unit> UnitManager::getUnitById(uint32_t id) const
	{
		const auto it = _unitsMap.find(id);
		return it != _unitsMap.end() ? it->second : nullptr;
	}

	std::vector<std::shared_ptr<Unit>> UnitManager::getUnits() const
	{
		return _units;
	}

	bool UnitManager::hasActiveUnits() const
	{
		return _units.size() > 1 && std::ranges::any_of(_units, [](const auto& unit) { return unit->isActive(); });
	}
}
