#pragma once

#include <Game/Component.hpp>
#include <cstdint>

namespace sw
{
	class Unit;
	struct GameContext;

	class MeleeAttackComponent final : public Component
	{
	public:
		MeleeAttackComponent(int32_t strength) :
				strength(strength)
		{}

		void update(const std::shared_ptr<Unit>& self, GameContext& ctx) override;

	private:
		int32_t strength;
	};
}
