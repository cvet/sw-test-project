#include <Game/Unit.hpp>

namespace sw
{
	Unit::Unit(uint32_t id, pos_t position) :
			_id(id),
			_position(position)
	{}

	uint32_t Unit::getId() const
	{
		return _id;
	}

	pos_t Unit::getPosition() const
	{
		return _position;
	}

	bool Unit::isActive() const
	{
		return _active;
	}

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
