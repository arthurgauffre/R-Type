/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DamageComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
class DamageComponent : public AComponent {
public:
  /**
   * @class DamageComponent
   * @brief Component that represents the damage capability of an entity.
   *
   * This component is used to define the damage that an entity can inflict.
   *
   * @param entityID The unique identifier of the entity.
   * @param damage The amount of damage the entity can inflict.
   */
  DamageComponent(uint32_t entityID, int damage);

  /**
   * @brief Destroy the DamageComponent object.
   */
  ~DamageComponent();

  /**
   * @brief Sets the damage value for the component.
   *
   * @param damage The amount of damage to set.
   */
  void setDamage(int damage);

  /**
   * @brief Retrieves the damage value.
   *
   * @return int The amount of damage.
   */
  int getDamage();

  /**
   * @brief Updates the damage value.
   *
   * This function sets the internal damage value to the specified amount.
   *
   * @param damage The new damage value to be set.
   */
  void update(int damage) { _damage = damage; };

private:
  /**
   * @brief Represents the damage value of a component.
   */
  int _damage;
};
} // namespace component