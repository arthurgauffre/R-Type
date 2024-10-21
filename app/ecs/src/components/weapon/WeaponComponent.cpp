/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponComponent
*/

#include <components/WeaponComponent.hpp>

/**
 * @brief Constructs a new WeaponComponent object.
 * 
 * @param entityID The ID of the entity to which this component belongs.
 * @param weaponEntityID The ID of the weapon entity associated with this component.
 * @param isAlwaysFiring A boolean indicating whether the weapon is always firing.
 * @param velocity The velocity of the weapon.
 */
component::WeaponComponent::WeaponComponent(uint32_t entityID,
                                            uint32_t weaponEntityID,
                                            bool isAlwaysFiring, float velocity)
    : AComponent(entityID), _weaponEntityID(weaponEntityID),
      _velocity(velocity) {
  _isFiring = isAlwaysFiring;
}

/**
 * @brief Destructor for the WeaponComponent class.
 *
 * This destructor is responsible for cleaning up any resources
 * allocated by the WeaponComponent instance. It ensures that
 * when a WeaponComponent object is destroyed, all associated
 * resources are properly released.
 */
component::WeaponComponent::~WeaponComponent() {}

/**
 * @brief Retrieves the ID of the weapon entity associated with this component.
 * 
 * @return uint32_t The ID of the weapon entity.
 */
uint32_t component::WeaponComponent::getWeaponEntityID() {
  return _weaponEntityID;
}

/**
 * @brief Sets the weapon entity ID for the WeaponComponent.
 * 
 * This function assigns a new weapon entity ID to the WeaponComponent.
 * 
 * @param weaponEntityID The new weapon entity ID to be set.
 */
void component::WeaponComponent::setWeaponEntityID(uint32_t weaponEntityID) {
  _weaponEntityID = weaponEntityID;
}

/**
 * @brief Sets the firing state of the weapon.
 * 
 * This function updates the internal state to indicate whether the weapon is currently firing.
 * 
 * @param isFiring A boolean value where true indicates the weapon is firing, and false indicates it is not.
 */
void component::WeaponComponent::setIsFiring(bool isFiring) {
  _isFiring = isFiring;
}

/**
 * @brief Checks if the weapon component is currently firing.
 * 
 * @return true if the weapon component is firing, false otherwise.
 */
bool component::WeaponComponent::getIsFiring() { return _isFiring; }
