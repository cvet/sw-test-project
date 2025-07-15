#pragma once

#include <Game/Component.hpp>
#include <Game/Unit.hpp>
#include <cstdint>

namespace sw
{
	class Unit;
	struct GameContext;

	class RangedAttackComponent final : public Component
	{
	public:
		RangedAttackComponent(int32_t agility, int32_t rangeMin, int32_t rangeMax) :
				_agility(agility),
				_rangeMin(rangeMin),
				_rangeMax(rangeMax)
		{}

		void update(const std::shared_ptr<Unit>& self, GameContext& ctx) override;

	private:
		int32_t _agility{};
		int32_t _rangeMin{};
		int32_t _rangeMax{};
	};
}
