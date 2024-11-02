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
  /**
   * @brief Construct a new CooldownComponent object
   *
   * @param entityID The ID of the entity associated with this component
   * @param cooldown The cooldown duration in seconds
   */
  CooldownComponent(uint32_t entityID, float cooldown);

  /**
   * @brief Destructor for the CooldownComponent class.
   */
  ~CooldownComponent();

  /**
   * @brief Updates the cooldown and time remaining for the component.
   *
   * @param cooldown The new cooldown value to set.
   * @param timeRemaining The new time remaining value to set.
   */
  void update(float cooldown, float timeRemaining) {
    _cooldown = cooldown;
    _timeRemaining = timeRemaining;
  }

  /**
   * @brief Sets the cooldown duration.
   *
   * This function sets the cooldown duration for the component.
   *
   * @param cooldown The duration of the cooldown in seconds (as float).
   */
  void setCooldown(float cooldown);

  /**
   * @brief Get the current cooldown value.
   *
   * @return The cooldown value as a float.
   */
  float getCooldown();

  /**
   * @brief Sets the remaining cooldown time.
   *
   * This function updates the remaining time for the cooldown period.
   *
   * @param timeRemaining The time remaining for the cooldown in seconds (as float).
   */
  void setTimeRemaining(float timeRemaining);

  /**
   * @brief Get the remaining cooldown time.
   *
   * @return The remaining time in seconds as a float.
   */
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