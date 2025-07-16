#pragma once

#include <Essentials/Position.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace sw
{
	class Unit;

	class Map
	{
	public:
		explicit Map(int32_t width, int32_t height);

		int32_t getWidth() const;
		int32_t getHeight() const;

		const std::shared_ptr<Unit>& unitAtPos(pos_t pos) const;
		std::vector<std::shared_ptr<Unit>> getUnitsInRange(pos_t pos, int32_t rangeMin, int32_t rangeMax) const;
		std::optional<pos_t> findNextStep(pos_t from, pos_t to) const;

		void addUnit(const std::shared_ptr<Unit>& unit);
		void removeUnit(const std::shared_ptr<Unit>& unit);
		void moveUnit(const std::shared_ptr<Unit>& unit, pos_t pos);

	private:
		std::shared_ptr<Unit>& mutableUnitAtPos(pos_t pos);
		void verifyPosition(pos_t pos) const;

		int32_t _width{};
		int32_t _height{};
		std::vector<std::shared_ptr<Unit>> _grid{};
	};
}
