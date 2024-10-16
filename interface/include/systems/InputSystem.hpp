/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#pragma once

#include <components/InputComponent.hpp>
#include <r-type/ASystem.hpp>

#include <iostream>

namespace ECS_system {
class InputSystem : public ASystem {
public:
  InputSystem(component::ComponentManager &componentManager,
              entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}
  ~InputSystem() = default;

  std::vector<std::string> update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities,
              std::vector<std::string> msgToSend) override;

  void initialize() override {}
  void handleComponents() override {}

private:
};
} // namespace ECS_system