/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ASystem
*/

#pragma once

#include "ISystem.hpp"
#include "ComponentManager.hpp"
#include <vector>
#include <memory>
namespace ECS_system
{
    class ASystem : public ISystem
    {
    public:
        ASystem(component::ComponentManager &componentManager) : _componentManager(componentManager) {}
        virtual ~ASystem() = default;

        // Init method
        virtual void initialize() = 0;

        // Update method called each frame
        virtual void update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) = 0;

        // Handle components method
        virtual void handleComponents() = 0;

    protected:
        component::ComponentManager &_componentManager;
    };
}
