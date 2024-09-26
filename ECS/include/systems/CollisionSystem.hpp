/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

#pragma once

#include "ASystem.hpp"
#include "HitBoxComponent.hpp"
#include "PositionComponent.hpp"

#include <vector>
#include <memory>
#include <iostream>

namespace ECS_system
{
    class CollisionSystem : public ASystem
    {
    public:
        CollisionSystem(component::ComponentManager &componentManager) : ASystem(componentManager) {}
        ~CollisionSystem() = default;

        void update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) override;

        void initialize() override {};
        void handleComponents() override {};

    private:
        void handleCollision(component::HitBoxComponent *hitbox1, component::HitBoxComponent *hitbox2);
        bool isColliding(component::HitBoxComponent *hitbox1, component::HitBoxComponent *hitbox2);
    };
}