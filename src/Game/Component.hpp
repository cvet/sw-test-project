#pragma once

#include <memory>

namespace sw
{
	class Unit;
	struct GameContext;

	class Component : public std::enable_shared_from_this<Component>
	{
	public:
		virtual ~Component() = default;

		virtual void update(const std::shared_ptr<Unit>& self, GameContext& ctx)
		{
			(void)self;
			(void)ctx;
		}
	};
}
