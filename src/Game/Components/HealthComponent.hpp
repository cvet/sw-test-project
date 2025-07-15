#pragma once

#include <Game/Component.hpp>
#include <cstdint>

namespace sw
{
	class HealthComponent final : public Component
	{
	public:
		HealthComponent(int32_t health) :
				_health(health)
		{}

		int getHealth() const
		{
			return _health;
		}

		void damage(int amount)
		{
			_health -= amount;
		}

		bool isAlive() const
		{
			return _health > 0;
		}

	private:
		int32_t _health{};
	};
}
