/*
** EPITECH PROJECT, 2024
** *
** File description:
** IEntity
*/

#pragma once

#include <cstdint>

namespace entity
{
    class IEntity
    {
    public:
        virtual ~IEntity() = default;

        // Return entity's ID
        virtual uint32_t getID() const = 0;

        // Enable or disable the entity
        virtual void setActive(bool active) = 0;

        // Verify if the entity is active
        virtual bool getActive() const = 0;
    };
}
