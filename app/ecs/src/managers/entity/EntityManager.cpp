/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EntityManager
*/

#include <managers/EntityManager.hpp>
#include <r-type/Entity.hpp>

/**
 * @brief Constructs an EntityManager object.
 */
entity::EntityManager::EntityManager() : _entityCounter(0) {}

/**
 * @brief Retrieves an entity by its unique identifier.
 *
 * This function iterates through the list of entities and returns the entity
 * that matches the given ID. If no entity with the specified ID is found,
 * the function returns nullptr.
 *
 * @param id The unique identifier of the entity to retrieve.
 * @return entity::IEntity* Pointer to the entity with the specified ID, or
 * nullptr if not found.
 */
entity::IEntity *entity::EntityManager::getEntityByID(uint32_t id) const
{
  for (auto &entity : _entities)
  {
    if (entity->getID() == id)
      return entity.get();
  }
  return nullptr;
}

/**
 * @brief Destroys an entity with the specified ID.
 *
 * This function removes the entity with the given ID from the list of entities.
 * It uses the erase-remove idiom to find and remove the entity.
 *
 * @param id The ID of the entity to be destroyed.
 */
void entity::EntityManager::destroyEntity(uint32_t id)
{
  _entities.erase(std::remove_if(_entities.begin(), _entities.end(),
                                 [id](const std::shared_ptr<IEntity> &entity)
                                 {
                                   return entity->getID() == id;
                                 }),
                  _entities.end());
}

/**
 * @brief Creates a new entity with the given ID and adds it to the entity
 * manager.
 *
 * This function creates a new entity of type `Entity` with the specified ID,
 * adds it to the list of managed entities, and returns a pointer to the newly
 * created entity.
 *
 * @param id The unique identifier for the new entity.
 * @return A pointer to the newly created entity.
 */
entity::IEntity *entity::EntityManager::createEntity(uint32_t id)
{
  _entities.push_back(std::make_unique<entity::Entity>(id));
  return _entities.back().get();
}

/**
 * @brief Retrieves the list of entities managed by the EntityManager.
 *
 * @return A reference to a vector of unique pointers to IEntity objects.
 */
std::vector<std::shared_ptr<entity::IEntity>> &
entity::EntityManager::getEntities()
{
  return _entities;
}

/**
 * @brief Generates a new unique identifier for an entity.
 *
 * This function generates a new unique identifier for an entity by incrementing
 * the ID counter and returning the new ID.
 *
 * @return uint32_t The new unique identifier for an entity.
 */
uint32_t entity::EntityManager::generateEntityID() { return _entityCounter++; }

#include <iostream>

/**
 * @brief Removes an entity with the specified ID from the list of entities.
 *
 * This function removes the entity with the given ID from the list of entities.
 * It uses the erase-remove idiom to find and remove the entity.
 *
 * @param id The ID of the entity to be removed.
 */
void entity::EntityManager::removeEntity(uint32_t id)
{
  _entities.erase(std::remove_if(_entities.begin(), _entities.end(),
                                 [id](const std::shared_ptr<IEntity> &entity)
                                 {
                                   return entity->getID() == id;
                                 }),
                  _entities.end());
}