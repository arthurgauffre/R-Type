/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ServerReceiveSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

namespace ECS_system {
class ServerReceiveSystem : virtual public ASystem {
public:
  ServerReceiveSystem(component::ComponentManager &componentManager,
                      entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}
  ~ServerReceiveSystem() = default;

  std::vector<std::string>
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::string> msgToSend) override;
  void initialize() override{};
  void handleComponents() override{};
};
} // namespace ECS_system