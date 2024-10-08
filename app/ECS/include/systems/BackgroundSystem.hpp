/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundSystem
*/

#pragma once

#include "ASystem.hpp"
#include "BackgroundComponent.hpp"
#include "ScrollComponent.hpp"
#include "PositionComponent.hpp"

namespace ECS_system
{
    class BackgroundSystem : public ASystem
    {
    public:
        BackgroundSystem(component::ComponentManager &componentManager)
            : ASystem(componentManager) {}
        ~BackgroundSystem() = default;

        void update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) override;

        void initialize() override {};
        void handleComponents() override {};
    };
}