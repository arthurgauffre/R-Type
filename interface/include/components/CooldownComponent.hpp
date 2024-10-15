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

  void update(float deltaTime) override {}

  void setCooldown(float cooldown);
  float getCooldown();

  void setTimeRemaining(float timeRemaining);
  float getTimeRemaining();

private:
  float _cooldown;
  float _timeRemaining;
};
} // namespace component