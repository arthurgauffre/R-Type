/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
class HealthComponent : public AComponent {
public:
  HealthComponent(uint32_t entityID, int health);
  ~HealthComponent();

  int getHealth();
  void setHealth(int health);

  void update(int health);

private:
  /**
   * @brief Represents the health of an entity.
   *
   * This member variable stores the current health points of an entity.
   * It is used to determine the entity's survivability and can be modified
   * by various game mechanics such as taking damage or healing.
   */
  int _health;
};
} // namespace component
