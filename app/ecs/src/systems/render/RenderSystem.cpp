/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#include <iostream>
#include <systems/RenderSystem.hpp>

/**
 * @brief Construct a new RenderSystem object.
 *
 * @param componentManager Reference to the ComponentManager that manages the
 * components.
 * @param window Reference to the SFML RenderWindow where the rendering will
 * take place.
 */
ECS_system::RenderSystem::RenderSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager,
    IGraphic &graphic)
    : ASystem(componentManager, entityManager, graphic) {}


/**
 * @brief Updates the render system by drawing all entities with the appropriate
 * components.
 *
 * This function clears the window, processes entities with background and
 * transform components to draw background sprites, and processes entities with
 * transform, sprite, and texture components to draw textured sprites. Finally,
 * it displays the window and handles window events.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be processed.
 */
 
void ECS_system::RenderSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend,
    std::vector<std::pair<std::string, size_t>> &msgReceived) {

  _graphic.clear();

  for (auto &entity : _componentManager.getEntitiesWithComponents<
                      component::SpriteComponent, component::TransformComponent,
                      component::TextureComponent, component::SizeComponent,
                      component::SpriteComponent>(entities)) {
    if (!entity->getActive() || _componentManager
        .getComponent<component::TypeComponent>(entity->getID())
        ->getType() != component::Type::BACKGROUND)
      continue;

  
    auto spriteComponent = _componentManager.getComponent<component::SpriteComponent>(entity->getID());
    auto textureComponent = _componentManager.getComponent<component::TextureComponent>(entity->getID());
    auto transformComponent = _componentManager.getComponent<component::TransformComponent>(entity->getID());

  
    uint32_t spriteId = spriteComponent->getSpriteId();
    _graphic.setTexture(spriteId, textureComponent->getTextureId());
    _graphic.setPosition(spriteId, transformComponent->getPosition().first, transformComponent->getPosition().second);

    _graphic.drawSprite(spriteId);
  }

  
  for (auto &entity : _componentManager.getEntitiesWithComponents<
                      component::TransformComponent, component::SpriteComponent,
                      component::TextureComponent, component::TypeComponent>(entities)) {
    if (!entity->getActive() || _componentManager
        .getComponent<component::TypeComponent>(entity->getID())
        ->getType() == component::Type::BACKGROUND)
      continue;

    auto transformComponent = _componentManager.getComponent<component::TransformComponent>(entity->getID());
    auto spriteComponent = _componentManager.getComponent<component::SpriteComponent>(entity->getID());
    auto textureComponent = _componentManager.getComponent<component::TextureComponent>(entity->getID());

    uint32_t spriteId = spriteComponent->getSpriteId();

    _graphic.setTexture(spriteId, textureComponent->getTextureId());
    _graphic.setPosition(spriteId, transformComponent->getPosition().first, transformComponent->getPosition().second);
    _graphic.setRotation(spriteId, transformComponent->getRotation());
    _graphic.setScale(spriteId, transformComponent->getScale().first, transformComponent->getScale().second);

    _graphic.drawSprite(spriteId);
  }

  _graphic.display();

  _graphic.handleEvents();
}
EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, IGraphic &graphic) {
  return new ECS_system::RenderSystem(componentManager, entityManager, graphic);
}