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
                 entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic);
  ~CooldownSystem();

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<entity::SceneStatus> &sceneStatus) override;
  void initialize() override {}
  void handleComponents() override {}

private:
};
} // namespace ECS_system