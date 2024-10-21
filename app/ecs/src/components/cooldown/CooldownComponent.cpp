/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownComponent
*/

#include <components/CooldownComponent.hpp>

/**
 * @brief Constructs a new CooldownComponent object.
 * 
 * @param entityID The ID of the entity this component is associated with.
 * @param cooldown The cooldown duration for the component.
 */
component::CooldownComponent::CooldownComponent(uint32_t entityID,
                                                float cooldown)
    : AComponent(entityID), _cooldown(cooldown), _timeRemaining(0) {}

component::CooldownComponent::~CooldownComponent() {}

/**
 * @brief Sets the cooldown value for the component.
 * 
 * @param cooldown The cooldown duration to be set.
 */
void component::CooldownComponent::setCooldown(float cooldown) {
  _cooldown = cooldown;
}

/**
 * @brief Retrieves the current cooldown value.
 * 
 * This function returns the cooldown value stored in the CooldownComponent.
 * 
 * @return float The current cooldown value.
 */
float component::CooldownComponent::getCooldown() { return _cooldown; }

/**
 * @brief Sets the remaining cooldown time.
 * 
 * This function sets the remaining time for the cooldown period.
 * 
 * @param timeRemaining The time remaining for the cooldown in seconds.
 */
void component::CooldownComponent::setTimeRemaining(float timeRemaining) {
  _timeRemaining = timeRemaining;
}

/**
 * @brief Retrieves the remaining cooldown time.
 * 
 * This function returns the amount of time left before the cooldown period ends.
 * 
 * @return float The remaining cooldown time in seconds.
 */
float component::CooldownComponent::getTimeRemaining() {
  return _timeRemaining;
}