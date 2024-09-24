/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <ASystem.hpp>
#include <PositionComponent.hpp>

namespace ECS_system
{
    class RenderSystem : public ASystem
    {
    public:
        RenderSystem(component::ComponentManager &componentManager, sf::RenderWindow &window)
            : ASystem(componentManager), window(window) {};
        ~RenderSystem() = default;

        void update(float deltaTime, std::vector<std::unique_ptr<entity::IEntity>> entities) override;
        void initialize() override {};
        void handleComponents() override {};

    private:
        sf::RenderWindow &window; // Reference to the window
    };
}