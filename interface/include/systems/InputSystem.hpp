/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#pragma once

#include <components/CooldownComponent.hpp>
#include <components/InputComponent.hpp>
#include <components/WeaponComponent.hpp>
#include <r-type/ASystem.hpp>

#include <iostream>

namespace ECS_system {
class InputSystem : public ASystem {
public:
  InputSystem(component::ComponentManager &componentManager,
              entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}
  ~InputSystem() = default;

  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, entity::SceneStatus &sceneStatus) override;

  void initialize() override {}
  void handleComponents() override {}

private:
};
} // namespace ECS_system