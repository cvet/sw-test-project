#include <Game/Map.hpp>
#include <Game/Unit.hpp>
#include <cassert>
#include <stdexcept>
#include <string>

namespace sw
{
	Map::Map(int32_t width, int32_t height) :
			_width(width),
			_height(height),
			_grid(static_cast<size_t>(width) * height)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Map dimensions must be positive");
		}
	}

	int32_t Map::getWidth() const
	{
		return _width;
	}

	int32_t Map::getHeight() const
	{
		return _height;
	}

	void Map::addUnit(const std::shared_ptr<Unit>& unit)
	{
		pos_t pos = unit->getPosition();
		verifyPosition(pos);
		mutableUnitAtPos(pos) = unit;
	}

	void Map::removeUnit(const std::shared_ptr<Unit>& unit)
	{
		pos_t pos = unit->getPosition();
		verifyPosition(pos);
		assert(unitAtPos(pos) == unit && "Removing a unit that is not present at the specified position");
		mutableUnitAtPos(pos).reset();
	}

	const std::shared_ptr<Unit>& Map::unitAtPos(pos_t pos) const
	{
		verifyPosition(pos);
		return _grid[pos.y * _width + pos.x];
	}

	std::shared_ptr<Unit>& Map::mutableUnitAtPos(pos_t pos)
	{
		verifyPosition(pos);
		return _grid[pos.y * _width + pos.x];
	}

	std::vector<std::shared_ptr<Unit>> Map::getUnitsInRange(pos_t pos, int32_t rangeMin, int32_t rangeMax) const
	{
		verifyPosition(pos);

		std::vector<std::shared_ptr<Unit>> units;

		for (int32_t oy = -rangeMax; oy <= rangeMax; ++oy)
		{
			for (int32_t ox = -rangeMax; ox <= rangeMax; ++ox)
			{
				auto checkPos = pos_t(pos.x + ox, pos.y + oy);

				if (checkPos.x < 0 || checkPos.x >= _width || checkPos.y < 0 || checkPos.y >= _height)
				{
					continue;
				}
				if (checkPos.distanceTo(pos) < rangeMin)
				{
					continue;
				}

				const auto& enemy = unitAtPos(checkPos);

				if (enemy)
				{
					units.emplace_back(enemy);
				}
			}
		}

		return units;
	}

	std::optional<pos_t> Map::findNextStep(pos_t from, pos_t to) const
	{
		verifyPosition(from);
		verifyPosition(to);

		if (from == to)
		{
			return std::nullopt;
		}

		// Calculate the first step towards the target position
		pos_t firstStep;

		int32_t dx = to.x - from.x;
		int32_t dy = to.y - from.y;

		if (std::abs(dx) > std::abs(dy))
		{
			firstStep.x = (dx > 0 ? 1 : -1);
			firstStep.y = (dy > 0 ? 1 : -1) * std::abs(dy) / std::abs(dx);
		}
		else
		{
			firstStep.x = (dx > 0 ? 1 : -1) * std::abs(dx) / std::abs(dy);
			firstStep.y = (dy > 0 ? 1 : -1);
		}

		pos_t steps[8] = {{1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}};
		const auto it = std::ranges::find_if(steps, [&](const pos_t& step) { return step == firstStep; });
		auto firstIndex = std::distance(steps, it);

		// Check all 8 possible directions starting from the first step
		for (int32_t i = 0; i < 8; i++)
		{
			pos_t nextStep = from + steps[(firstIndex + i) % 8];

			if (nextStep.x >= 0 && nextStep.x < _width && nextStep.y >= 0 && nextStep.y < _height
				&& !unitAtPos(nextStep))
			{
				return nextStep;
			}
		}

		return std::nullopt;
	}

	void Map::moveUnit(const std::shared_ptr<Unit>& unit, pos_t pos)
	{
		verifyPosition(pos);

		if (mutableUnitAtPos(pos))
		{
			throw std::runtime_error(
				"Cannot move unit to occupied position: " + std::to_string(pos.x) + ", " + std::to_string(pos.y));
		}

		removeUnit(unit);
		unit->setPosition(pos);
		addUnit(unit);
	}

	void Map::verifyPosition(pos_t pos) const
	{
		if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
		{
			throw std::out_of_range("Position out of bounds");
		}
	}
}
