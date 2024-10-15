/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownSystem
*/

#pragma once

#include <r-type/ASystem.hpp>
#include <components/CooldownComponent.hpp>

namespace ECS_system
{
    class CooldownSystem : virtual public ASystem
    {
    public:
        CooldownSystem(component::ComponentManager &componentManager,
                       entity::EntityManager &entityManager);
        ~CooldownSystem();

        void update(float deltaTime,
                    std::vector<std::shared_ptr<entity::IEntity>> entities) override;
        void initialize() override {}
        void handleComponents() override {}

    private:
    };
}