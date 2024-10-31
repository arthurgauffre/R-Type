/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Entity
*/

#include <r-type/Entity.hpp>

namespace entity {
/**
 * @brief Constructs a new Entity object with the given ID.
 *
 * This constructor initializes an Entity with a specified ID and sets its
 * active status to true.
 *
 * @param id The unique identifier for the entity.
 */
entity::Entity::Entity(uint32_t id, int numClt) : id(id), isActive(true), numClient(numClt) {}

/**
 * @brief Destructor for the Entity class.
 *
 * This destructor is responsible for cleaning up any resources
 * allocated by the Entity class. It is defined as the default
 * destructor, meaning it will automatically handle the destruction
 * of member variables and base class subobjects.
 */
entity::Entity::~Entity() = default;

/**
 * @brief Retrieves the unique identifier of the entity.
 *
 * @return uint32_t The unique identifier of the entity.
 */
uint32_t entity::Entity::getID() const { return id; }

/**
 * @brief Sets the active state of the entity.
 *
 * This function sets the active state of the entity to the specified value.
 *
 * @param active A boolean value indicating the desired active state.
 *               If true, the entity is set to active. If false, the entity is
 * set to inactive.
 */
void entity::Entity::setActive(bool active) { isActive = active; }

/**
 * @brief Checks if the entity is active.
 *
 * This function returns the current active state of the entity.
 *
 * @return true if the entity is active, false otherwise.
 */
bool entity::Entity::getActive() const { return isActive; }

EntityCommunication entity::Entity::getCommunication() const { return communicationStatus; }

void entity::Entity::setCommunication(EntityCommunication communication) { communicationStatus = communication; }

Scene entity::Entity::getSceneStatus() const { return sceneStatus; }

void entity::Entity::setSceneStatus(Scene status) { sceneStatus = status; }

int entity::Entity::getNumClient() const { return numClient; }

void entity::Entity::setNumClient(int num) { numClient = num; }
} // namespace entity
