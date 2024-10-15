/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#include <systems/WeaponSystem.hpp>
#include <iostream>

ECS_system::WeaponSystem::WeaponSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

ECS_system::WeaponSystem::~WeaponSystem() {}

void ECS_system::WeaponSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities)
{
    for (auto &entity : _componentManager.getEntitiesWithComponents<component::WeaponComponent>(entities))
    {
        component::WeaponComponent *weaponComponent = _componentManager.getComponent<component::WeaponComponent>(entity.get()->getID());
        if (weaponComponent->getLastFireTime() >= weaponComponent->getCooldown())
            weaponComponent->setIsFiring(false);
        if (weaponComponent->getIsFiring() == true)
        {
            weaponComponent->setLastFireTime(0);

            std::cout << "Firing" << std::endl;

            weaponComponent->setIsFiring(false);
        }
    }
}

void ECS_system::WeaponSystem::createProjectile(uint32_t entityID, std::string texturePath, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f scale, int damage)
{
    // auto weapon = this->_entityManager.createEntity(entityID);
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
    return new ECS_system::WeaponSystem(componentManager, entityManager);
}