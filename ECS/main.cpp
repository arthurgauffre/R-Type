/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <iostream>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "AEntity.hpp"
#include "AComponent.hpp"
#include "PositionComponent.hpp"

int main()
{
    // Créer des gestionnaires d'entités et de composants
    entity::EntityManager entityManager;
    component::ComponentManager componentManager;

    // Créer une entité
    auto *entity = entityManager.createEntity(0);

    // Créer un composant
    auto *component = componentManager.addComponent<component::PositionComponent>(0, 10.0f, 20.0f);

    // Ajouter le composant à l'entité
    std::cout << "State of entity :" << entityManager.getEntityByID(0)->getActive() << std::endl;
    std::cout << "Position of entity : " << componentManager.getComponent<component::PositionComponent>(0)->getX() << ":" << componentManager.getComponent<component::PositionComponent>(0)->getY() << std::endl;

    return 0;
}