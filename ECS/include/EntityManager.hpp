/*
** EPITECH PROJECT, 2024
** *
** File description:
** EntityManager
*/

#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>
#include "IEntity.hpp"
#include <memory>

namespace entity
{
    class EntityManager
    {
    public:
        EntityManager() = default;

        // Create a new entity with a specific ID
        IEntity *createEntity(uint32_t id);

        // Destroy an entity by its ID
        void destroyEntity(uint32_t id);

        // Get an entity by its ID
        IEntity *getEntityByID(uint32_t id) const;

        // Get all entities
        std::vector<std::shared_ptr<IEntity>> &getEntities();

    private:
        // Stock all entities
        std::vector<std::shared_ptr<IEntity>> _entities;
    };
}
