/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

/**
 * @brief Checks if two hitboxes are colliding.
 *
 * This function determines whether two hitboxes, represented by their respective
 * HitBoxComponent objects, are colliding based on their positions and dimensions.
 *
 * @param hitbox1 A shared pointer to the first HitBoxComponent.
 * @param hitbox2 A shared pointer to the second HitBoxComponent.
 * @return true if the hitboxes are colliding, false otherwise.
 */
bool ECS_system::CollisionSystem::isColliding(component::HitBoxComponent *hitbox1, component::HitBoxComponent *hitbox2)
{
    component::PositionComponent *pos1 = _componentManager.getComponent<component::PositionComponent>(hitbox1->getEntityID());
    component::PositionComponent *pos2 = _componentManager.getComponent<component::PositionComponent>(hitbox2->getEntityID());

    // Check if the hitboxes are colliding
    if (pos1->getX() < pos2->getX() + hitbox2->getWidth() &&
        pos1->getX() + hitbox1->getWidth() > pos2->getX() &&
        pos1->getY() < pos2->getY() + hitbox2->getHeight() &&
        pos1->getY() + hitbox1->getHeight() > pos2->getY())
        return true;
    return false;
}

/**
 * @brief Handles the collision between two hitboxes.
 *
 * This function is called when a collision is detected between two entities' hitboxes.
 * It processes the collision event and performs necessary actions.
 *
 * @param hitbox1 A shared pointer to the first entity's HitBoxComponent.
 * @param hitbox2 A shared pointer to the second entity's HitBoxComponent.
 */
void ECS_system::CollisionSystem::handleCollision(component::HitBoxComponent *hitbox1, component::HitBoxComponent *hitbox2)
{
    std::cout << "Collision detected" << std::endl;
}

/**
 * @brief Updates the collision system by checking for collisions between entities.
 *
 * This function iterates through a list of entities, retrieves their HitBoxComponents,
 * and checks for collisions between them. If a collision is detected, it handles the collision.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be checked for collisions.
 */
void ECS_system::CollisionSystem::update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities)
{
    for (auto &entity : entities)
    {
        component::HitBoxComponent *hitbox1 = _componentManager.getComponent<component::HitBoxComponent>(entity->getID());

        if (hitbox1 == nullptr)
            continue;
        for (auto &entity2 : entities)
        {
            component::HitBoxComponent *hitbox2 = _componentManager.getComponent<component::HitBoxComponent>(entity2->getID());

            if (hitbox2 == nullptr)
                continue;
            if (hitbox1->getEntityID() == hitbox2->getEntityID())
                continue;
            if (isColliding(hitbox1, hitbox2))
                handleCollision(hitbox1, hitbox2);
        }
    }
}