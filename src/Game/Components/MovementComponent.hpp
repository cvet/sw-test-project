#pragma once

#include <Essentials/Position.hpp>
#include <Game/Component.hpp>
#include <optional>

namespace sw
{
	class Unit;
	struct GameContext;

	class MovementComponent final : public Component
	{
	public:
		MovementComponent() = default;

		void setTarget(pos_t target);
		void update(const std::shared_ptr<Unit>& self, GameContext& ctx) override;

	private:
		std::optional<pos_t> _moveTarget{};
	};
}
