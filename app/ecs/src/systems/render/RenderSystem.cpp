/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#include <systems/RenderSystem.hpp>

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

    for (auto &entity :
         _componentManager
             .getEntitiesWithComponents<component::PositionComponent>(entities))
    {
        component::PositionComponent *positionComponent =
            _componentManager.getComponent<component::PositionComponent>(
                entity.get()->getID());
        component::SpriteComponent *spriteComponent =
            _componentManager.getComponent<component::SpriteComponent>(
                entity.get()->getID());
        component::TextureComponent *textureComponent =
            _componentManager.getComponent<component::TextureComponent>(
                entity.get()->getID());

        spriteComponent->getSprite().setPosition(positionComponent->getX(),
                                                 positionComponent->getY());
        spriteComponent->getSprite().setTexture(textureComponent->getTexture());

        _window.draw(spriteComponent->getSprite());
    }
    _window.display();
}

extern "C" std::shared_ptr<ECS_system::ISystem> createRenderSystem(
    component::ComponentManager &componentManager, sf::RenderWindow &window)
{
    return std::make_shared<ECS_system::RenderSystem>(componentManager, window);
}