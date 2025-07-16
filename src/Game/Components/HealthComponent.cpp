#include <Game/Components/HealthComponent.hpp>
#include <algorithm>

namespace sw
{
	HealthComponent::HealthComponent(int32_t health) :
			_health(health)
	{}

	bool HealthComponent::isAlive() const
	{
		return _health > 0;
	}

	int HealthComponent::getHealth() const
	{
		return _health;
	}

	void HealthComponent::damage(int amount)
	{
		_health -= amount;
		_health = std::max(_health, 0);
	}
}
