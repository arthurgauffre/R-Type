/*
** EPITECH PROJECT, 2024
** *
** File description:
** AEntity
*/

#pragma once

#include "IEntity.hpp"

namespace entity
{
    class AEntity : public IEntity
    {
    public:
        AEntity(uint32_t id) : id(id), isActive(true) {}

        virtual ~AEntity() = default;

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
