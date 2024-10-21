/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameSystem
*/

#include <systems/GameSystem.hpp>

/**
 * @brief Constructs a new GameSystem object.
 *
 * @param componentManager Reference to the ComponentManager.
 * @param entityManager Reference to the EntityManager.
 */
ECS_system::GameSystem::GameSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

/**
 * @brief Destructor for the GameSystem class.
 *
 * This destructor is responsible for cleaning up any resources
 * or performing any necessary finalization tasks when a GameSystem
 * object is destroyed.
 */
ECS_system::GameSystem::~GameSystem() {}

/**
 * @brief Updates the game system by processing the entities.
 *
 * This function iterates through the provided entities and counts the number
 * of players and enemies. If there are no players, it throws a GameLoosed
 * exception indicating the game is over. If there are no enemies, it throws
 * a GameWon exception indicating the player has won.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to the entities to be processed.
 *
 * @throws rtype::GameLoosed If there are no players left in the game.
 * @throws rtype::GameWon If there are no enemies left in the game.
 */
void ECS_system::GameSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  int _playerCount = 0;
  int _enemyCount = 0;

  for (auto &entity : entities) {
    component::TypeComponent *type =
        _componentManager.getComponent<component::TypeComponent>(
            entity->getID());

    if (!type)
      continue;

    if (type->getType() == "player")
      _playerCount++;

    if (type->getType() == "enemy")
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