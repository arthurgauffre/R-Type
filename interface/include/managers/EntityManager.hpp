/*
** EPITECH PROJECT, 2024
** *
** File description:
** EntityManager
*/

#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <r-type/IEntity.hpp>
#include <vector>

namespace entity {
class EntityManager {
public:
  /**
   * @brief Constructs an EntityManager object.
   */
  EntityManager();

  /**
   * @brief Creates a new entity with the specified ID and client number.
   *
   * @param id The unique identifier for the entity.
   * @param numClt The client number associated with the entity.
   * @return A pointer to the newly created IEntity object.
   */
  IEntity *createEntity(uint32_t id, int numClt);

  /**
   * @brief Retrieves an entity by its unique identifier.
   *
   * @param id The unique identifier of the entity to retrieve.
   * @return A pointer to the entity with the specified ID, or nullptr if no such entity exists.
   */
  IEntity *getEntityByID(uint32_t id) const;

  /**
   * @brief Generates a unique entity ID.
   *
   * This function generates a new unique identifier for an entity. Each call to this function
   * will return a different ID, ensuring that all entities have distinct identifiers.
   *
   * @return uint32_t The generated unique entity ID.
   */
  uint32_t generateEntityID();

  /**
   * @brief Retrieves a reference to the vector of entities managed by the EntityManager.
   *
   * @return std::vector<std::shared_ptr<IEntity>>& Reference to the vector of shared pointers to IEntity objects.
   */
  std::vector<std::shared_ptr<IEntity>> &getEntities();

  /**
   * @brief Removes an entity from the manager by its unique identifier.
   *
   * This function will remove the entity associated with the given ID from the
   * entity manager. If the entity does not exist, the function will have no effect.
   *
   * @param id The unique identifier of the entity to be removed.
   */
  void removeEntity(uint32_t id);

private:
  /**
   * @brief A container that holds shared pointers to IEntity objects.
   *
   * This vector is used to manage and store entities within the EntityManager.
   * Each entity is managed through a std::shared_ptr to ensure proper memory
   * management and to allow shared ownership of the entities.
   */
  std::vector<std::shared_ptr<IEntity>> _entities;

  /**
   * @brief Counter to keep track of the number of entities.
   *
   * This variable is used to assign unique IDs to each entity created by the EntityManager.
   */
  uint32_t _entityCounter;
};
} // namespace entity
