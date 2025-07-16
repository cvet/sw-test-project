#include <Game/Components/HealthComponent.hpp>
#include <Game/Components/RangedAttackComponent.hpp>
#include <Game/GameContext.hpp>
#include <Game/Unit.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw
{
	RangedAttackComponent::RangedAttackComponent(int32_t agility, int32_t rangeMin, int32_t rangeMax) :
			_agility(agility),
			_rangeMin(rangeMin),
			_rangeMax(rangeMax)
	{}

	void RangedAttackComponent::update(const std::shared_ptr<Unit>& self, GameContext& ctx)
	{
		if (!ctx.map.getUnitsInRange(self->getPosition(), 1, 1).empty())
		{
			return;
		}

		auto targets = ctx.map.getUnitsInRange(self->getPosition(), _rangeMin, _rangeMax);

		if (!targets.empty())
		{
			const auto& target = ctx.random.getAny(targets);

			if (auto health = target->getComponent<HealthComponent>())
			{
				health->damage(_agility);
				self->markActive();

				ctx.logger.log(
					ctx.tick,
					io::UnitAttacked{
						.attackerUnitId = self->getId(),
						.targetUnitId = target->getId(),
						.damage = static_cast<uint32_t>(_agility),
						.targetHp = static_cast<uint32_t>(health->getHealth())});
			}
		}
	}
}
