/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Isystem
*/

#pragma once

#include <vector>
#include <memory>
#include "IEntity.hpp"

namespace ECS_system
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        // Init method
        virtual void initialize() = 0;

        // Update method called each frame
        virtual void update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) = 0;

        // Handle components method
        virtual void handleComponents() = 0;
    };
}
