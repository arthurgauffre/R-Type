/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponComponent
*/

#include <components/WeaponComponent.hpp>

component::WeaponComponent::WeaponComponent(uint32_t entityID,
                                            uint32_t weaponEntityID,
                                            bool isAlwaysFiring, float velocity)
    : AComponent(entityID), _weaponEntityID(weaponEntityID),
      _velocity(velocity) {
  _isFiring = isAlwaysFiring;
  this->_communication = ComponentCommunication::SERVERONLY;
}

component::WeaponComponent::~WeaponComponent() {}

uint32_t component::WeaponComponent::getWeaponEntityID() {
  return _weaponEntityID;
}

void component::WeaponComponent::setWeaponEntityID(uint32_t weaponEntityID) {
  _weaponEntityID = weaponEntityID;
}

void component::WeaponComponent::setIsFiring(bool isFiring) {
  _isFiring = isFiring;
}

bool component::WeaponComponent::getIsFiring() { return _isFiring; }
