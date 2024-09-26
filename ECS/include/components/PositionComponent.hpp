/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PositionComponent
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class PositionComponent : public AComponent
    {
    public:
        PositionComponent(uint32_t entityID, float x, float y)
            : AComponent(entityID), _x(x), _y(y) {};
        ~PositionComponent() = default;

        float getX() const { return _x; } // Return the x position
        float getY() const { return _y; } // Return the y position

        void update(float deltaTime) override {}; // Update the component

    private:
        float _x; // x position
        float _y; // y position
    };
}