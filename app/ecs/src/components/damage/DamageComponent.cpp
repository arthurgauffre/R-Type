/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DamageComponent
*/

#include <components/DamageComponent.hpp>

/**
 * @brief Constructs a new DamageComponent object.
 *
 * @param entityID The unique identifier for the entity associated with this
 * component.
 * @param damage The amount of damage this component represents.
 */
component::DamageComponent::DamageComponent(uint32_t entityID, int damage)
    : AComponent(entityID), _damage(damage) {}

/**
 * @brief Destroys the DamageComponent object.
 */
component::DamageComponent::~DamageComponent() {}

/**
 * @brief Sets the damage value for the DamageComponent.
 *
 * @param damage The new damage value to be set.
 */
void component::DamageComponent::setDamage(int damage) {
  this->_damage = damage;
}

/**
 * @brief Retrieves the damage value of the DamageComponent.
 *
 * @return int The damage value.
 */
int component::DamageComponent::getDamage() { return this->_damage; }