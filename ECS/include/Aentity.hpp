/*
** EPITECH PROJECT, 2024
** *
** File description:
** Aentity
*/

#pragma once

#include "Ientity.hpp"

namespace entity
{
    class Aentity : public Ientity
    {
    public:
        Aentity(uint32_t id) : id(id), isActive(true) {}

        virtual ~Aentity() = default;

        uint32_t getID() const override
        {
            return id;
        }

        void setActive(bool active) override
        {
            isActive = active;
        }

        bool getActive() const override
        {
            return isActive;
        }

    protected:
        uint32_t id;
        bool isActive;
    };
}
