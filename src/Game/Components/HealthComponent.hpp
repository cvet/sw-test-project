#pragma once

#include <Game/Component.hpp>
#include <cstdint>

namespace sw
{
	class HealthComponent final : public Component
	{
	public:
		HealthComponent(int32_t health);

		bool isAlive() const;
		int getHealth() const;
		void damage(int amount);

	private:
		int32_t _health{};
	};
}
