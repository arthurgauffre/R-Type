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

  IEntity *createEntity(uint32_t id, int numClt);

  IEntity *getEntityByID(uint32_t id) const;

  uint32_t generateEntityID();

  std::vector<std::shared_ptr<IEntity>> &getEntities();

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

  uint32_t _entityCounter;
};
} // namespace entity
