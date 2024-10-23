/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownSystem
*/

#pragma once

#include <components/CooldownComponent.hpp>
#include <r-type/ASystem.hpp>

namespace ECS_system {
class CooldownSystem : virtual public ASystem {
public:
  CooldownSystem(component::ComponentManager &componentManager,
                 entity::EntityManager &entityManager);
  ~CooldownSystem();

  std::vector<std::string> update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::string> msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) override;
  void initialize() override {}
  void handleComponents() override {}

private:
};
} // namespace ECS_system