/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <iostream>
#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "AEntity.hpp"

#include "ComponentManager.hpp"
#include "PositionComponent.hpp"
#include "AComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextureComponent.hpp"

#include "SystemManager.hpp"
#include "RenderSystem.hpp"
#include "ASystem.hpp"

int main()
{
    entity::EntityManager entityManager;
    component::ComponentManager componentManager;
    ECS_system::SystemManager systemManager;

    entity::IEntity *entity = entityManager.createEntity(0);

    component::PositionComponent *component = componentManager.addComponent<component::PositionComponent>(0, 700.0f, 500.0f);
    component::SpriteComponent *spriteComponent = componentManager.addComponent<component::SpriteComponent>(0, 700.0f, 500.0f);
    component::TextureComponent *textureComponent = componentManager.addComponent<component::TextureComponent>(0, "../sprites/r-typesheet1.gif");

    // create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS");
    systemManager.addSystem<ECS_system::RenderSystem>(componentManager, window);

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update systems
        systemManager.update(0.0f, entityManager.getEntities());
    }

    return 0;
}