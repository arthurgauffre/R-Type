/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#pragma once

#include <r-type/ASystem.hpp>
#include <components/InputComponent.hpp>

#include <iostream>

namespace ECS_system {
class InputSystem : public ASystem {
public:
  InputSystem(component::ComponentManager &componentManager)
      : ASystem(componentManager) {}
  ~InputSystem() = default;

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities) override;

  void initialize() override {}
  void handleComponents() override {}

private:
};
} // namespace ECS_system