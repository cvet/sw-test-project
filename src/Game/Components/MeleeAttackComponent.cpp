#include <Essentials/Random.hpp>
#include <Game/Components/HealthComponent.hpp>
#include <Game/Components/MeleeAttackComponent.hpp>
#include <Game/GameContext.hpp>
#include <Game/Unit.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw
{
	void MeleeAttackComponent::update(const std::shared_ptr<Unit>& self, GameContext& ctx)
	{
		auto targets = ctx.map.getUnitsInRange(self->getPosition(), 1, 1);

		if (!targets.empty())
		{
			const auto& target = ctx.random.getAny(targets);

			if (auto health = target->getComponent<HealthComponent>())
			{
				health->damage(strength);
				self->markActive();

				ctx.logger.log(
					ctx.tick,
					io::UnitAttacked{
						.attackerUnitId = self->getId(),
						.targetUnitId = target->getId(),
						.damage = static_cast<uint32_t>(strength),
						.targetHp = static_cast<uint32_t>(health->getHealth())});
			}
		}
	}
}
