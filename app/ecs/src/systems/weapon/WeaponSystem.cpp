/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#include <iostream>
#include <systems/WeaponSystem.hpp>

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
        component::CooldownComponent *cooldownComponent = _componentManager.getComponent<component::CooldownComponent>(weaponComponent->getWeaponEntityID());

        if (weaponComponent->getIsFiring() == true && cooldownComponent->getTimeRemaining() > 0)
            weaponComponent->setIsFiring(false);

        if (weaponComponent->getIsFiring() == true)
        {
            std::cout << "Firing" << std::endl;

            cooldownComponent->setTimeRemaining(cooldownComponent->getCooldown());
            weaponComponent->setIsFiring(false);
        }
    }
}

void ECS_system::WeaponSystem::createProjectile(
    uint32_t entityID, std::string texturePath, sf::Vector2f position,
    sf::Vector2f velocity, sf::Vector2f scale, int damage)
{
    // auto weapon = this->_entityManager.createEntity(entityID);
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
    return new ECS_system::WeaponSystem(componentManager, entityManager);
}