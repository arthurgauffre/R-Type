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
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities)
{
    _window.clear();

    for (auto &entity : _componentManager.getEntitiesWithComponents<component::BackgroundComponent, component::PositionComponent>(entities))
    {
        component::BackgroundComponent *backgroundComponent = _componentManager.getComponent<component::BackgroundComponent>(entity->getID());
        component::PositionComponent *positionComponent = _componentManager.getComponent<component::PositionComponent>(entity->getID());

        sf::Vector2f position = {positionComponent->getX(), positionComponent->getY()};
        sf::Sprite sprite = backgroundComponent->getSprite();
        sf::Sprite duplicateSprite = backgroundComponent->getDuplicateSprite();

        sprite.setPosition(position);
        duplicateSprite.setPosition(position.x + backgroundComponent->getSize().x, position.y);

        _window.draw(sprite);
        _window.draw(duplicateSprite);
    }

    for (auto &entity :
         _componentManager
             .getEntitiesWithComponents<component::TransformComponent, component::SpriteComponent, component::TextureComponent>(
                 entities))
    {
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
