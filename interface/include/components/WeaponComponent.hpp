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
  WeaponComponent(uint32_t entityID, uint32_t weaponEntityID,
                  bool isAlwaysFiring = false, float velocity = 0);
  ~WeaponComponent();

  void update(uint32_t weaponEntityID, bool _isFiring, float _velocity) {
    this->_isFiring = _isFiring;
    this->_velocity = _velocity;
    this->_weaponEntityID = weaponEntityID;
  }

  uint32_t getWeaponEntityID();
  void setWeaponEntityID(uint32_t weaponEntityID);

  void setIsFiring(bool isFiring);
  bool getIsFiring();

  void setVelocity(float velocity) { _velocity = velocity; }
  float getVelocity() { return _velocity; }

private:
  uint32_t _weaponEntityID;
  bool _isFiring;
  float _velocity;
};
} // namespace component
