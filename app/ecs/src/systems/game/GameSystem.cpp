/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameSystem
*/

#include <systems/GameSystem.hpp>

ECS_system::GameSystem::GameSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

ECS_system::GameSystem::~GameSystem() {}

void ECS_system::GameSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) {
  int _playerCount = 0;
  int _enemyCount = 0;

  for (auto &entity : entities) {
    component::TypeComponent *type =
        _componentManager.getComponent<component::TypeComponent>(
            entity->getID());

    if (!type)
      continue;

    if (type->getType() == component::Type::PLAYER)
      _playerCount++;

    if (type->getType() == component::Type::ENEMY)
      _enemyCount++;
  }

  if (_playerCount == 0)
    throw rtype::GameLoosed("Game Over");

  if (_enemyCount == 0)
    throw rtype::GameWon("You Win");
}

extern "C" ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::GameSystem(componentManager, entityManager);
}