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

#include "SystemManager.hpp"
#include "RenderSystem.hpp"
#include "ASystem.hpp"

int main()
{
    // Créer des gestionnaires d'entités et de composants
    entity::EntityManager entityManager;
    component::ComponentManager componentManager;
    ECS_system::SystemManager systemManager;

    // Créer une entité
    auto *entity = entityManager.createEntity(0);

    // Add component to entity
    auto *component = componentManager.addComponent<component::PositionComponent>(0, 10.0f, 20.0f);

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