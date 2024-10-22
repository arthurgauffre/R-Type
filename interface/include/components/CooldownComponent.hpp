/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
class CooldownComponent : public AComponent {
public:
  CooldownComponent(uint32_t entityID, float cooldown);
  ~CooldownComponent();

  void update(float cooldown, float timeRemaining) {
    _cooldown = cooldown;
    _timeRemaining = timeRemaining;
  }

  void setCooldown(float cooldown);
  float getCooldown();

  void setTimeRemaining(float timeRemaining);
  float getTimeRemaining();

private:
  float _cooldown;
  float _timeRemaining;
};
} // namespace component