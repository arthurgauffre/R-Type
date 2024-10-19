/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthComponent
*/

#include <components/HealthComponent.hpp>

/**
 * @brief Constructs a new HealthComponent object.
 *
 * @param entityID The ID of the entity this component is associated with.
 * @param health The initial health value for the component.
 */
component::HealthComponent::HealthComponent(uint32_t entityID, int health)
    : AComponent(entityID) {
  this->_health = health;
}

/**
 * @brief Destructor for the HealthComponent class.
 *
 * This destructor is responsible for cleaning up any resources
 * or performing any necessary finalization tasks when a
 * HealthComponent object is destroyed.
 */
component::HealthComponent::~HealthComponent() {}

/**
 * @brief Retrieves the current health value of the component.
 *
 * @return int The current health value.
 */
int component::HealthComponent::getHealth() { return this->_health; }

/**
 * @brief Sets the health value for the HealthComponent.
 *
 * @param health The new health value to be set.
 */
void component::HealthComponent::setHealth(int health) {
  this->_health = health;
}

void component::HealthComponent::update(int health) {
  this->_health = health;
}