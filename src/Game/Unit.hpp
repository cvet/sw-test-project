#pragma once

#include <Essentials/Position.hpp>
#include <Game/Component.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace sw
{
	struct GameContext;

	class Unit : public std::enable_shared_from_this<Unit>
	{
	public:
		explicit Unit(uint32_t id, pos_t position) :
				_id(id),
				_position(position)
		{}

		uint32_t getId() const
		{
			return _id;
		}

		pos_t getPosition() const
		{
			return _position;
		}

		bool isActive() const
		{
			return _active;
		}

		template <typename T>
		std::shared_ptr<T> getComponent() const;

		void setPosition(pos_t position);
		void addComponent(std::shared_ptr<Component> component);
		void update(GameContext& ctx);
		void markActive();

	private:
		uint32_t _id{};
		pos_t _position{};
		bool _active{true};
		std::vector<std::shared_ptr<Component>> _components{};
	};

	template <typename T>
	std::shared_ptr<T> Unit::getComponent() const
	{
		for (const auto& component : _components)
		{
			if (auto ptr = std::dynamic_pointer_cast<T>(component))
			{
				return ptr;
			}
		}
		return nullptr;
	}
}
