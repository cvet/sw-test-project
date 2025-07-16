#include <Game/Components/MovementComponent.hpp>
#include <Game/GameContext.hpp>
#include <Game/Unit.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/UnitMoved.hpp>

namespace sw
{
	void MovementComponent::setTarget(pos_t target)
	{
		_moveTarget = target;
	}

	void MovementComponent::update(const std::shared_ptr<Unit>& self, GameContext& ctx)
	{
		if (!_moveTarget.has_value())
		{
			return;
		}

		auto nextPos = ctx.map.findNextStep(self->getPosition(), _moveTarget.value());

		if (nextPos.has_value())
		{
			ctx.map.moveUnit(self, nextPos.value());
			self->markActive();

			ctx.logger.log(
				ctx.tick,
				io::UnitMoved{
					.unitId = self->getId(),
					.x = static_cast<uint32_t>(nextPos->x),
					.y = static_cast<uint32_t>(nextPos->y)});

			// Check if the unit has reached the target position
			if (nextPos == _moveTarget.value())
			{
				_moveTarget.reset();

				ctx.logger.log(
					ctx.tick,
					io::MarchEnded{
						.unitId = self->getId(),
						.x = static_cast<uint32_t>(nextPos->x),
						.y = static_cast<uint32_t>(nextPos->y)});
			}
		}
	}
}
