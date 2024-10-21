/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ServerSystem
*/

#include <ServerSystem.hpp>



EXPORT_API ECS_system::ISystem *createSystem(
    component::ComponentManager &componentManager, entity::EntityManager &entityManager)
{
    return new rtype::network::ServerSystem(componentManager, entityManager);
}