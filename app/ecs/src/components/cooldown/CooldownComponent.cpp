/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownComponent
*/

#include <components/CooldownComponent.hpp>

component::CooldownComponent::CooldownComponent(uint32_t entityID,
                                                float cooldown)
    : AComponent(entityID), _cooldown(cooldown), _timeRemaining(0) {}

component::CooldownComponent::~CooldownComponent() {}

void component::CooldownComponent::setCooldown(float cooldown) {
  _cooldown = cooldown;
}

float component::CooldownComponent::getCooldown() { return _cooldown; }

void component::CooldownComponent::setTimeRemaining(float timeRemaining) {
  _timeRemaining = timeRemaining;
}

float component::CooldownComponent::getTimeRemaining() {
  return _timeRemaining;
}