/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

#include <iostream>

namespace component {
class WeaponComponent : public AComponent {
public:
  /**
   * @brief Constructs a new WeaponComponent object.
   *
   * @param entityID The ID of the entity that owns this weapon component.
   * @param weaponEntityID The ID of the weapon entity associated with this component.
   * @param isAlwaysFiring Optional parameter to specify if the weapon is always firing. Defaults to false.
   * @param velocity Optional parameter to specify the velocity of the weapon. Defaults to 0.
   */
  WeaponComponent(uint32_t entityID, uint32_t weaponEntityID,
                  bool isAlwaysFiring = false, float velocity = 0);

  /**
   * @brief Destructor for the WeaponComponent class.
   *
   * This destructor is responsible for cleaning up any resources
   * that the WeaponComponent may have acquired during its lifetime.
   */
  ~WeaponComponent();

  /**
   * @brief Updates the weapon component with the given parameters.
   *
   * @param weaponEntityID The ID of the weapon entity to update.
   * @param _isFiring A boolean indicating whether the weapon is firing.
   * @param _velocity The velocity of the weapon.
   */
  void update(uint32_t weaponEntityID, bool _isFiring, float _velocity) {
    this->_isFiring = _isFiring;
    this->_velocity = _velocity;
    this->_weaponEntityID = weaponEntityID;
  }

  /**
   * @brief Retrieves the entity ID of the weapon.
   *
   * @return uint32_t The entity ID associated with the weapon.
   */
  uint32_t getWeaponEntityID();

  /**
   * @brief Sets the entity ID of the weapon.
   *
   * This function assigns a unique identifier to the weapon entity.
   *
   * @param weaponEntityID The unique identifier for the weapon entity.
   */
  void setWeaponEntityID(uint32_t weaponEntityID);

  /**
   * @brief Sets the firing state of the weapon.
   *
   * @param isFiring A boolean indicating whether the weapon is firing (true) or not (false).
   */
  void setIsFiring(bool isFiring);

  /**
   * @brief Checks if the weapon is currently firing.
   *
   * @return true if the weapon is firing, false otherwise.
   */
  bool getIsFiring();

  /**
   * @brief Sets the velocity of the weapon.
   *
   * @param velocity The new velocity value to be set.
   */
  void setVelocity(float velocity) { _velocity = velocity; }

  /**
   * @brief Get the velocity of the weapon.
   *
   * @return float The current velocity of the weapon.
   */
  float getVelocity() { return _velocity; }

private:
  /**
   * @brief Unique identifier for the weapon entity associated with this
   * component.
   */
  uint32_t _weaponEntityID;

  /**
   * @brief Indicates whether the weapon is currently firing.
   */
  bool _isFiring;

  /**
   * @brief Represents the velocity of the weapon.
   *
   * This variable stores the speed at which the weapon moves.
   */
  float _velocity;
};
} // namespace component
