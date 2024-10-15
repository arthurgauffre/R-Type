/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameSystem
*/

#pragma once

#include <r-type/ASystem.hpp>
#include <Error.hpp>

#include <components/TypeComponent.hpp>

namespace ECS_system
{
    class GameSystem : virtual public ASystem
    {
    public:
        GameSystem(component::ComponentManager &componentManager,
                   entity::EntityManager &entityManager);
        ~GameSystem();

        void update(float deltaTime,
                    std::vector<std::shared_ptr<entity::IEntity>> entities) override;

        void initialize() override {}
        void handleComponents() override {}

    protected:
    private:
    };
}