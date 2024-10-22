/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameSystem
*/

#pragma once

#include <Error.hpp>
#include <r-type/ASystem.hpp>

#include <components/TypeComponent.hpp>

namespace ECS_system {
class GameSystem : virtual public ASystem {
public:
  GameSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager);
  ~GameSystem();

  std::vector<std::string> update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::string> msgToSend) override;

  void initialize() override {}
  void handleComponents() override {}

protected:
private:
};
} // namespace ECS_system