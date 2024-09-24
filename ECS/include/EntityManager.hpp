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
#include "Ientity.hpp"
#include <memory>

namespace entity
{
    class EntityManager
    {
    public:
        EntityManager() = default;

        // Create a new entity with a specific ID
        Ientity *createEntity(uint32_t id);

        // Destroy an entity by its ID
        void destroyEntity(uint32_t id);

        // Get an entity by its ID
        Ientity *getEntityByID(uint32_t id) const;

    private:
        // Stock all entities
        std::vector<std::unique_ptr<Ientity>> entities;
    };
}
