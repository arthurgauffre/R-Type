/*
** EPITECH PROJECT, 2024
** *
** File description:
** AComponent
*/

#pragma once

#include "Icomponent.hpp"

namespace component
{
    class AComponent : public IComponent
    {
    public:
        AComponent(uint32_t entityID)
            : id(entityID), isActive(true) {}

        virtual ~AComponent() = default;

        // Return the entity's ID
        uint32_t getEntityID() const override
        {
            return id;
        }

        // Return the component's state
        bool getActive() const override
        {
            return isActive;
        }

        // Enable or disable the component
        void setActive(bool active) override
        {
            isActive = active;
        }

        // Update the component
        virtual void update(float deltaTime) = 0;

    protected:
        uint32_t id;   // Id of the associated entity
        bool isActive; // State of the component
    };
}
