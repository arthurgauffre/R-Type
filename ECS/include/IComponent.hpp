/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IComponent
*/

#pragma once

#include <cstdint>

namespace component
{
    class IComponent
    {
    public:
        virtual ~IComponent() = default;

        // Return the entity's ID
        virtual uint32_t getEntityID() const = 0;

        // Update the component
        virtual void update(float deltaTime) = 0;

        // Return the component's type
        virtual bool getActive() const = 0;

        // Enable or disable the component
        virtual void setActive(bool active) = 0;
    };
}