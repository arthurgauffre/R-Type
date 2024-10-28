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
  /**
   * @brief Represents the cooldown period for an action or ability.
   *
   * This member variable stores the duration of the cooldown in seconds.
   * It is used to determine how long an action or ability must wait before it
   * can be used again.
   */
  float _cooldown;

  /**
   * @brief Represents the remaining cooldown time.
   *
   * This variable holds the amount of time left before an action can be
   * performed again.
   */
  float _timeRemaining;
};
} // namespace component