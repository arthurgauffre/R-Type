/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include <iostream>

/**
 * @brief Updates the render system by drawing all entities with
 * PositionComponent, SpriteComponent, and TextureComponent.
 *
 * This function clears the window, iterates through all entities that have a
 * PositionComponent, retrieves the corresponding PositionComponent,
 * SpriteComponent, and TextureComponent for each entity, sets the sprite's
 * position and texture, and then draws the sprite to the window. Finally, it
 * displays the window.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be processed.
 */
void ECS_system::RenderSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  _window.clear();

  for (auto &entity :
       _componentManager
           .getEntitiesWithComponents<component::TransformComponent>(
               entities)) {
    component::TransformComponent *transformComponent =
        _componentManager.getComponent<component::TransformComponent>(
            entity.get()->getID());
    component::SpriteComponent *spriteComponent =
        _componentManager.getComponent<component::SpriteComponent>(
            entity.get()->getID());
    component::TextureComponent *textureComponent =
        _componentManager.getComponent<component::TextureComponent>(
            entity.get()->getID());

    spriteComponent->getSprite().setTexture(textureComponent->getTexture());
    spriteComponent->getSprite().setPosition(transformComponent->getPosition());
    spriteComponent->getSprite().setRotation(transformComponent->getRotation());
    spriteComponent->getSprite().setScale(transformComponent->getScale());

    _window.draw(spriteComponent->getSprite());
  }
  _window.display();
}
