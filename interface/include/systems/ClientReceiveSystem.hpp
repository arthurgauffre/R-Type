/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientReceiveSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

namespace ECS_system {
class ClientReceiveSystem : virtual public ASystem {
public:
  ClientReceiveSystem(component::ComponentManager &componentManager,
                      entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}
  ~ClientReceiveSystem() = default;

  std::vector<std::string>
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::string> msgToSend) override;
  void initialize() override{};
  void handleComponents() override{};
};
} // namespace ECS_system