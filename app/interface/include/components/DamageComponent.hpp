/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DamageComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component
{
    class DamageComponent : public AComponent
    {
    public:
        DamageComponent(uint32_t entityID, int damage);
        ~DamageComponent();

        void setDamage(int damage);
        int getDamage();

    private:
        int _damage;
    };
}