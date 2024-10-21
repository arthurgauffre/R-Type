/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** VelocityComponent
*/

#include <components/VelocityComponent.hpp>

namespace component {
/**
 * @brief Constructs a new VelocityComponent object.
 * 
 * @param entityID The ID of the entity associated with this component.
 * @param velocity The desired velocity of the entity as a pair of floats (x, y).
 * @param actualVelocity The actual velocity of the entity as a pair of floats (x, y).
 */
VelocityComponent::VelocityComponent(uint32_t entityID,
                                     std::pair<float, float> velocity,
                                     std::pair<float, float> actualVelocity)
    : AComponent(entityID), _velocity(velocity),
      _actualVelocity(actualVelocity) {}
} // namespace component