/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

#include <iostream>

namespace component
{
    class WeaponComponent : public AComponent
    {
    public:
        WeaponComponent(uint32_t entityID, uint32_t weaponEntityID);
        ~WeaponComponent();

  void update(float deltaTime) override {}

        uint32_t getWeaponEntityID();
        void setWeaponEntityID(uint32_t weaponEntityID);

        void setIsFiring(bool isFiring);
        bool getIsFiring();
    private:
        uint32_t _weaponEntityID;
        bool _isFiring;
    };
}
