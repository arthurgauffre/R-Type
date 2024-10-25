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
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities)
{
  _window.clear();

  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::SpriteComponent, component::TransformComponent, component::TextureComponent, component::SizeComponent, component::SpriteComponent>(
           entities))
  {
    if (entity.get()->getActive() == false || _componentManager.getComponent<component::TypeComponent>(entity.get()->getID())->getType() != "background")
      continue;
    component::SpriteComponent *spriteComponent =
        _componentManager.getComponent<component::SpriteComponent>(
            entity->getID());
    component::TextureComponent *textureComponent =
        _componentManager.getComponent<component::TextureComponent>(
            entity->getID());
    component::TransformComponent *transformComponent =
        _componentManager.getComponent<component::TransformComponent>(
            entity->getID());
    component::SizeComponent *sizeComponent =
        _componentManager.getComponent<component::SizeComponent>(
            entity->getID());

    sf::Vector2f position = {transformComponent->getPosition().first,
                             transformComponent->getPosition().second};
    sf::Sprite sprite = spriteComponent->getSprite();
    sf::Texture backgroundTexture = textureComponent->getTexture();

    sprite.setTexture(backgroundTexture);
    sprite.setPosition(position);

    _window.draw(sprite);
  }

  for (auto &entity : _componentManager.getEntitiesWithComponents<
                      component::TransformComponent, component::SpriteComponent,
                      component::TextureComponent>(entities))
  {

    if (entity.get()->getActive() == false || _componentManager.getComponent<component::TypeComponent>(entity.get()->getID())->getType() == "background")
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

    sf::Vector2f SfPosition = {transformComponent->getPosition().first,
                               transformComponent->getPosition().second};

    sf::Vector2f SfScale = {transformComponent->getScale().first,
                            transformComponent->getScale().second};

    spriteComponent->getSprite().setTexture(textureComponent->getTexture());
    spriteComponent->getSprite().setPosition(SfPosition);
    spriteComponent->getSprite().setRotation(transformComponent->getRotation());
    spriteComponent->getSprite().setScale(SfScale);

    _window.draw(spriteComponent->getSprite());
  }
  _window.display();

  // sf event
  while (_window.pollEvent(_event))
  {
    if (_event.type == sf::Event::Closed)
    {
      _window.close();
      // this->_gameClosed = true;
    }
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
  return new ECS_system::RenderSystem(componentManager, entityManager);
}