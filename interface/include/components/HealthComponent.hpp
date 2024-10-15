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

  int getDamageIncoming();
  void setDamageIncoming(int damage);

  void update(float deltaTime) override;

private:
  /**
   * @brief Represents the health of an entity.
   *
   * This member variable stores the current health points of an entity.
   * It is used to determine the entity's survivability and can be modified
   * by various game mechanics such as taking damage or healing.
   */
  int _health;

  /**
   * @brief Represents the amount of incoming damage to the entity.
   *
   * This variable holds the value of damage that the entity is about to
   * receive. It is used to calculate the reduction of the entity's health when
   * damage is applied.
   */
  int _damageIncoming;
};
} // namespace component
