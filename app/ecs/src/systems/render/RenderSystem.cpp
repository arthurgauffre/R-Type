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
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager),
      _window(sf::VideoMode(1920, 1080), "R-Type"), _event(sf::Event()) {}

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
std::vector<std::string> ECS_system::RenderSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::string> msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) {
  _window.clear();

  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::BackgroundComponent, component::PositionComponent>(
           entities)) {
    component::BackgroundComponent *backgroundComponent =
        _componentManager.getComponent<component::BackgroundComponent>(
            entity->getID());
    component::PositionComponent *positionComponent =
        _componentManager.getComponent<component::PositionComponent>(
            entity->getID());

    sf::Vector2f position = {positionComponent->getX(),
                             positionComponent->getY()};
    sf::Sprite sprite = backgroundComponent->getSprite();
    sf::Sprite duplicateSprite = backgroundComponent->getDuplicateSprite();

    sprite.setPosition(position);
    duplicateSprite.setPosition(position.x + backgroundComponent->getSize().x,
                                position.y);

    _window.draw(sprite);
    _window.draw(duplicateSprite);
  }

  for (auto &entity : _componentManager.getEntitiesWithComponents<
                      component::TransformComponent, component::SpriteComponent,
                      component::TextureComponent>(entities)) {

    if (entity.get()->getActive() == false)
      continue;
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

  // sf event
  while (_window.pollEvent(_event)) {
    if (_event.type == sf::Event::Closed) {
      _window.close();
      // this->_gameClosed = true;
    }
  }
  return msgToSend;
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::RenderSystem(componentManager, entityManager);
}