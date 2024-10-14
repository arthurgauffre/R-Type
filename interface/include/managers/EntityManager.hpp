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

  IEntity *createEntity(uint32_t id);

  void destroyEntity(uint32_t id);

  IEntity *getEntityByID(uint32_t id) const;

  std::vector<std::shared_ptr<IEntity>> &getEntities();

private:
  /**
   * @brief A container that holds shared pointers to IEntity objects.
   *
   * This vector is used to manage and store entities within the EntityManager.
   * Each entity is managed through a std::shared_ptr to ensure proper memory
   * management and to allow shared ownership of the entities.
   */
  std::vector<std::shared_ptr<IEntity>> _entities;
};
} // namespace entity
