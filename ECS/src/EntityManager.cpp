/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EntityManager
*/

#include "EntityManager.hpp"
#include "Aentity.hpp"

/**
 * @brief Retrieves an entity by its unique identifier.
 *
 * This function iterates through the list of entities and returns the entity
 * that matches the given ID. If no entity with the specified ID is found,
 * the function returns nullptr.
 *
 * @param id The unique identifier of the entity to retrieve.
 * @return entity::Ientity* Pointer to the entity with the specified ID, or nullptr if not found.
 */
entity::Ientity *entity::EntityManager::getEntityByID(uint32_t id) const
{
    for (auto &entity : entities)
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
    entities.erase(std::remove_if(entities.begin(), entities.end(), [id](const std::unique_ptr<Ientity> &entity)
                                  { return entity->getID() == id; }),
                   entities.end());
}

/**
 * @brief Creates a new entity with the given ID and adds it to the entity manager.
 *
 * This function creates a new entity of type `Aentity` with the specified ID,
 * adds it to the list of managed entities, and returns a pointer to the newly created entity.
 *
 * @param id The unique identifier for the new entity.
 * @return A pointer to the newly created entity.
 */
entity::Ientity *entity::EntityManager::createEntity(uint32_t id)
{
    entities.push_back(std::make_unique<entity::Aentity>(id));
    return entities.back().get();
}