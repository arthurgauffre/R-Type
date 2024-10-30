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
    entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic)
    : ASystem(componentManager, entityManager, graphic) {
        _graphic->createWindow(1920, 1080, "R-Type");
    }

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
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<entity::SceneStatus> &sceneStatus) {
  _graphic->windowClear();

  // lock the entity mutex
  std::lock_guard<std::mutex> lock(entityMutex);
  for (auto &entity : _componentManager.getEntitiesWithComponents<
                      component::SpriteComponent, component::TransformComponent,
                      component::TextureComponent, component::SizeComponent,
                      component::SpriteComponent>(entities)) {
     if (entity->getSceneStatus() != *sceneStatus)
      continue;
     if (entity.get()->getActive() == false ||
        _componentManager
                .getComponent<component::TypeComponent>(entity.get()->getID())
                ->getType() != component::Type::BACKGROUND)
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

    std::pair<float, float> position = {transformComponent->getPosition().first,
                             transformComponent->getPosition().second};
    size_t sprite = spriteComponent->getSpriteId();
    size_t backgroundTexture = textureComponent->getTexture();

    _graphic->setSpriteTexture(sprite, backgroundTexture);
    _graphic->setSpritePosition(position.first, position.second, sprite);

    _graphic->drawSprite(sprite);
  }

  for (auto &entity : _componentManager.getEntitiesWithComponents<
                      component::TransformComponent, component::SpriteComponent,
                      component::TextureComponent, component::TypeComponent>(entities)) {
    if (entity->getSceneStatus() != *sceneStatus)
      continue;
     if (entity.get()->getActive() == false ||
        _componentManager
                .getComponent<component::TypeComponent>(entity.get()->getID())
                ->getType() == component::Type::BACKGROUND)
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

    std::pair<float, float> Position = {transformComponent->getPosition().first,
                               transformComponent->getPosition().second};

    std::pair<float, float> Scale = {transformComponent->getScale().first,
                            transformComponent->getScale().second};

    _graphic->setSpriteTexture(spriteComponent->getSpriteId(),
                               textureComponent->getTexture());
    _graphic->setSpritePosition(Position.first, Position.second,
                                spriteComponent->getSpriteId());
    _graphic->setSpriteRotation(transformComponent->getRotation(),
                                spriteComponent->getSpriteId());
    _graphic->setSpriteScale(Scale.first, Scale.second,
                             spriteComponent->getSpriteId());

    _graphic->drawSprite(spriteComponent->getSpriteId());
  }
  _graphic->windowDisplay();

  _graphic->eventHandler();
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic) {
  return new ECS_system::RenderSystem(componentManager, entityManager, graphic);
}