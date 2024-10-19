/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** VelocityComponent
*/

#include <components/VelocityComponent.hpp>

namespace component {
VelocityComponent::VelocityComponent(uint32_t entityID, std::pair <float, float> velocity,
                                     std::pair <float, float> actualVelocity)
    : AComponent(entityID), _velocity(velocity),
      _actualVelocity(actualVelocity) {}
} // namespace component