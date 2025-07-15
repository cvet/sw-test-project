#include <Game/Unit.hpp>

namespace sw
{
	void Unit::setPosition(pos_t position)
	{
		_position = position;
	}

	void Unit::addComponent(std::shared_ptr<Component> component)
	{
		_components.emplace_back(std::move(component));
	}

	void Unit::update(GameContext& ctx)
	{
		_active = false;

		for (const auto& component : _components)
		{
			component->update(shared_from_this(), ctx);
		}
	}

	void Unit::markActive()
	{
		_active = true;
	}
}
