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
  /**
   * @brief Constructs a new HealthComponent object.
   *
   * @param entityID The unique identifier of the entity.
   * @param health The initial health value of the entity.
   */
  HealthComponent(uint32_t entityID, int health);

  /**
   * @brief Destructor for the HealthComponent class.
   *
   * This destructor is responsible for cleaning up any resources
   * allocated by the HealthComponent instance before it is destroyed.
   */
  ~HealthComponent();

  /**
   * @brief Get the current health value.
   *
   * @return int The current health.
   */
  int getHealth();

  /**
   * @brief Sets the health value for the component.
   *
   * @param health The new health value to be set.
   */
  void setHealth(int health);

  /**
   * @brief Updates the health value of the component.
   *
   * @param health The new health value to be set.
   */
  void update(int health) {
    this->_health = health;
  };

  /**
   * @brief Retrieves the amount of incoming damage.
   *
   * This function returns the amount of damage that is incoming to the entity.
   * It can be used to determine how much damage the entity is about to take.
   *
   * @return int The amount of incoming damage.
   */
  int getDamageIncoming();

  /**
   * @brief Sets the incoming damage to the health component.
   *
   * This function updates the health component with the specified amount of damage
   * that is incoming. It is used to apply damage to the entity that this component
   * is attached to.
   *
   * @param damage The amount of damage to be applied.
   */
  void setDamageIncoming(int damage);

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
