/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundSystem
*/

#pragma once

#include <components/BackgroundComponent.hpp>
#include <components/PositionComponent.hpp>
#include <components/ScrollComponent.hpp>
#include <r-type/ASystem.hpp>

namespace ECS_system {
class BackgroundSystem : public ASystem {
public:
  BackgroundSystem(component::ComponentManager &componentManager,
                   entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}
  ~BackgroundSystem() = default;

  std::vector<std::string> update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities,
              std::vector<std::string> msgToSend) override;

  void initialize() override{};
  void handleComponents() override{};
};
} // namespace ECS_system