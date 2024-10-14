/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#include <CoreModule.hpp>
// #include <Error.hpp>

/**
 * @brief Construct a new rtype::Core Module::Core Module object
 *
 */
rtype::CoreModule::CoreModule() {
  this->_componentManager = std::make_shared<component::ComponentManager>();
  this->_systemManager = std::make_shared<ECS_system::SystemManager>();
  this->_entityManager = std::make_shared<entity::EntityManager>();
}

/**
 * @brief Destroy the rtype::Core Module::Core Module object
 *
 */
rtype::CoreModule::~CoreModule() {}

/**
 * @brief Retrieves the entity manager.
 *
 * This function returns a shared pointer to the EntityManager associated with
 * the CoreModule. The EntityManager is responsible for managing the entities
 * within the application.
 *
 * @return std::shared_ptr<entity::EntityManager> A shared pointer to the
 * EntityManager.
 */
std::shared_ptr<entity::EntityManager>
rtype::CoreModule::getEntityManager() const {
  return this->_entityManager;
}

/**
 * @brief Retrieves the component manager.
 *
 * This function returns a shared pointer to the component manager associated
 * with the CoreModule. The component manager is responsible for managing
 * various components within the module.
 *
 * @return std::shared_ptr<component::ComponentManager> Shared pointer to the
 * component manager.
 */
std::shared_ptr<component::ComponentManager>
rtype::CoreModule::getComponentManager() const {
  return this->_componentManager;
}

/**
 * @brief Retrieves the SystemManager instance.
 *
 * This function returns a shared pointer to the SystemManager instance
 * associated with the CoreModule. The SystemManager is responsible for
 * managing the various systems within the ECS (Entity Component System).
 *
 * @return std::shared_ptr<ECS_system::SystemManager> A shared pointer to the
 * SystemManager instance.
 */
std::shared_ptr<ECS_system::SystemManager>
rtype::CoreModule::getSystemManager() const {
  return this->_systemManager;
}

/**
 * @brief Runs the core module's main loop.
 *
 * This function starts a loop that continuously updates the system manager
 * with the elapsed time since the last update and the current entities from
 * the entity manager.
 */
void rtype::CoreModule::run() {
  sf::Clock clock;
  while (1) {
    float deltatime = clock.restart().asSeconds();
    this->getSystemManager()->update(deltatime,
                                     this->getEntityManager()->getEntities());
  }
}

/**
 * @brief Creates a background entity with the specified parameters.
 *
 * This function creates a background entity with the given entity ID, texture
 * path, scrolling speed, and size. It adds the necessary components to the
 * entity, including PositionComponent, ScrollComponent, and
 * BackgroundComponent.
 *
 * @param entityID The unique identifier for the entity.
 * @param texturePath The file path to the texture to be used for the
 * background.
 * @param speed The scrolling speed of the background.
 * @param size The size of the background.
 * @return A pointer to the created background entity.
 */
entity::IEntity *rtype::CoreModule::createBackground(uint32_t entityID,
                                                     std::string texturePath,
                                                     sf::Vector2f speed,
                                                     sf::Vector2f size) {
  auto background = this->getEntityManager()->createEntity(entityID);

  this->getComponentManager()->addComponent<component::PositionComponent>(
      entityID, 0.0f, 0.0f);
  this->getComponentManager()->addComponent<component::ScrollComponent>(
      entityID, speed);
  this->getComponentManager()->addComponent<component::BackgroundComponent>(
      entityID, texturePath, size);

  return background;
}

/**
 * @brief Creates a player entity with the specified components.
 *
 * This function creates a player entity with the given entity ID and
 * initializes it with various components including position, sprite, texture,
 * input, velocity, and transform components.
 *
 * @param entityID The unique identifier for the entity.
 * @param texturePath The file path to the texture to be used for the entity.
 * @param position The initial position of the entity.
 * @param velocity The initial velocity of the entity.
 * @param scale The scale of the entity.
 * @return A pointer to the created player entity.
 */
entity::IEntity *
rtype::CoreModule::createPlayer(uint32_t entityID, std::string texturePath,
                                sf::Vector2f position, sf::Vector2f velocity,
                                sf::Vector2f scale, int health) {
  auto player = this->getEntityManager()->createEntity(entityID);

  this->getComponentManager()->addComponent<component::PositionComponent>(
      entityID, position.x, position.y);
  this->getComponentManager()->addComponent<component::SpriteComponent>(
      entityID, position.x, position.y);
  this->getComponentManager()->addComponent<component::TextureComponent>(
      entityID, texturePath);
  this->getComponentManager()->addComponent<component::InputComponent>(
      entityID);
  this->getComponentManager()->addComponent<component::VelocityComponent>(
      entityID, velocity);
  this->getComponentManager()->addComponent<component::TransformComponent>(
      entityID, position, scale);
  this->getComponentManager()->addComponent<component::HealthComponent>(
      entityID, health);

  return player;
}

/**
 * @brief Initializes the core module of the R-Type game.
 *
 * This function sets up the initial state of the game by creating the player
 * and background entities, adding necessary systems to the system manager,
 * and binding input actions to specific keys.
 *
 * The following entities are created:
 * - Player with ID 0, sprite located at "app/assets/sprites/r-typesheet1.gif",
 *   initial position (100.0f, 100.0f), velocity (10.0f, 0.0f), and scale
 * (1.0f, 1.0f).
 * - Background with ID 1, image located at
 * "app/assets/images/city_background.png", initial position (100.0f, 0.0f), and
 * size (1920.0f, 1080.0f).
 *
 * The following systems are added to the system manager:
 * - Audio system
 * - Render system
 * - Input system
 * - Movement system
 * - Background system
 *
 * The following input actions are bound to keys for the player with ID 0:
 * - "MoveLeft" to the 'A' key
 * - "MoveRight" to the 'D' key
 * - "MoveUp" to the 'W' key
 * - "MoveDown" to the 'S' key
 */
void rtype::CoreModule::init() {
  auto player = this->createPlayer(
      0, "app/assets/sprites/plane.png", sf::Vector2f(100.0f, 100.0f),
      sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.5f, 0.5f), 1);
  this->createBackground(1, "app/assets/images/city_background.png",
                         sf::Vector2f(100.0f, 0.0f),
                         sf::Vector2f(1920.0f, 1080.0f));

  component::ComponentManager &componentManager = *this->getComponentManager();

  this->getSystemManager()->addSystem(componentManager, "audio");
  this->getSystemManager()->addSystem(componentManager, "render");
  this->getSystemManager()->addSystem(componentManager, "input");
  this->getSystemManager()->addSystem(componentManager, "movement");
  this->getSystemManager()->addSystem(componentManager, "background");
  this->getSystemManager()->addSystem(componentManager, "health");

  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveLeft", sf::Keyboard::A);
  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveRight", sf::Keyboard::D);
  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveUp", sf::Keyboard::W);
  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveDown", sf::Keyboard::S);
}