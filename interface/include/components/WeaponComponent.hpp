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
        WeaponComponent(uint32_t entityID, std::string type, float cooldown, int damage);
        ~WeaponComponent();

        void update(float deltaTime) override {}

        void setCooldown(float cooldown);
        float getCooldown();

        void setLastFireTime(float lastFireTime);
        float getLastFireTime();

        void setType(std::string type);
        std::string getType();

        void setIsFiring(bool isFiring);
        bool getIsFiring();

        void setDamage(int damage);
        int getDamage();

    private:
        std::string _type;
        float _cooldown;
        float _lastFireTime;
        int _damage;
        bool _isFiring;
    };
}
