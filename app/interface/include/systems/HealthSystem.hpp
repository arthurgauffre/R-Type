/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

#include <components/HealthComponent.hpp>

namespace ECS_system {
class HealthSystem : virtual public ASystem {
public:
  HealthSystem(component::ComponentManager &componentManager);
  ~HealthSystem();

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities) override;

  void initialize() override{};

  void handleComponents() override{};

private:
};
} // namespace ECS_system