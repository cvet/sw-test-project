#pragma once

#include <Game/Components/HealthComponent.hpp>
#include <Game/Components/MeleeAttackComponent.hpp>
#include <Game/Components/MovementComponent.hpp>
#include <Game/Components/RangedAttackComponent.hpp>
#include <Game/Unit.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace sw
{
	class UnitManager
	{
	public:
		UnitManager() = default;

		void addUnit(const std::shared_ptr<Unit>& unit);
		void removeUnit(const std::shared_ptr<Unit>& unit);
		std::shared_ptr<Unit> getUnitById(uint32_t id) const;
		std::vector<std::shared_ptr<Unit>> getUnits() const;
		bool hasActiveUnits() const;

		//
		// Фабричные методы для создания юнитов
		// Конфигурации лучше вынести в конфиги и компоновать юниты динамически
		//

		static std::shared_ptr<Unit> createSwordsman(uint32_t id, pos_t pos, int32_t hp, int32_t str)
		{
			auto unit = std::make_shared<Unit>(id, pos);
			unit->addComponent(std::make_unique<MovementComponent>());
			unit->addComponent(std::make_unique<HealthComponent>(hp));
			unit->addComponent(std::make_unique<MeleeAttackComponent>(str));
			return unit;
		}

		static std::shared_ptr<Unit> createHunter(
			uint32_t id, pos_t pos, int32_t hp, int32_t ag, int32_t str, int32_t range)
		{
			auto unit = std::make_shared<Unit>(id, pos);
			unit->addComponent(std::make_unique<MovementComponent>());
			unit->addComponent(std::make_unique<HealthComponent>(hp));
			unit->addComponent(std::make_unique<RangedAttackComponent>(ag, 2, range));
			unit->addComponent(std::make_unique<MeleeAttackComponent>(str));
			return unit;
		}

		//
		// Заготовки для новых типов юнитов
		// Мечник, Охотник, Стена, Башня, Лекарь, Ворон, Мина
		//

		/*class FlyingTagComponent : public Component
		{};

		class NoMeleeTargetableTag : public Component
		{};

		class NonBlockingComponent : public Component
		{};

		class UntargetableComponent : public Component
		{};

		static std::shared_ptr<Unit> createTower(int id, pos_t pos, int hp, int power)
		{
			auto unit = std::make_shared<Unit>(id, pos);
			unit->addComponent(std::make_unique<HealthComponent>(hp));
			unit->addComponent(std::make_unique<RangedAttackComponent>(power, 2, 5));
			return unit;
		}

		static std::shared_ptr<Unit> createHealer(int id, pos_t pos, int hp, int spirit)
		{
			auto unit = std::make_shared<Unit>(id, pos);
			unit->addComponent(std::make_shared<MovementComponent>());
			unit->addComponent(std::make_shared<HealthComponent>(hp));
			unit->addComponent(std::make_shared<HealingComponent>(spirit, 2));
			return unit;
		}

		static std::shared_ptr<Unit> createRaven(int id, pos_t pos, int hp, int agility)
		{
			auto unit = std::make_shared<Unit>(id, pos);
			unit->addComponent(std::make_shared<MovementComponent>(2));
			unit->addComponent(std::make_shared<HealthComponent>(hp));
			unit->addComponent(std::make_shared<MeleeAttackComponent>(agility));
			unit->addComponent(std::make_shared<FlyingTagComponent>());
			unit->addComponent(std::make_shared<NoMeleeTargetableTag>());
			return unit;
		}

		static std::shared_ptr<Unit> createMine(int id, pos_t pos, int power)
		{
			auto unit = std::make_shared<Unit>(id, pos);
			unit->addComponent(std::make_shared<ExplosiveComponent>(power, 2, 3));
			unit->addComponent(std::make_shared<NonBlockingComponent>());
			unit->addComponent(std::make_shared<UntargetableComponent>());
			return unit;
		}*/

	private:
		std::vector<std::shared_ptr<Unit>> _units{};
		std::unordered_map<uint32_t, std::shared_ptr<Unit>> _unitsMap{};
	};
}
