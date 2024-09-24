/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Isystem
*/

#pragma once

namespace system
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        // Init method
        virtual void initialize() = 0;

        // Update method called each frame
        virtual void update(float deltaTime) = 0;

        // Handle components method
        virtual void handleComponents() = 0;
    };
}
