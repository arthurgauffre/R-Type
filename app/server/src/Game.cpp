/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "../include/Game.hpp"

Game::Game(std::shared_ptr<rtype::CoreModule> coreModule) : _coreModule(coreModule)
{
}

Game::~Game()
{
}

entity::IEntity *Game::createWeapon(uint32_t parentID,
                                                 std::string type, int damage,
                                                 float cooldown) {
  auto weapon = _coreModule->getEntityManager()->createEntity(
      _coreModule->getEntityManager()->generateEntityID());

  _coreModule->getComponentManager()->addComponent<component::SoundComponent>(
      weapon->getID(), "app/assets/musics/blaster.wav");
  _coreModule->getComponentManager()->addComponent<component::TypeComponent>(
      weapon->getID(), type);
  _coreModule->getComponentManager()->addComponent<component::ParentComponent>(
      weapon->getID(), parentID);
//   _coreModule->getComponentManager()->addComponent<component::CooldownComponent>(
//       weapon->getID(), cooldown);

  return weapon;
}

/**
 * @brief Creates a background entity with the specified components.
 *
 * This function creates a background entity with the given entity ID and
 * initializes it with various components including type, music, transform, and
 * background components.
 *
 * @param entityID The unique identifier for the entity.
 * @param texturePath The file path to the texture to be used for the entity.
 * @param speed The speed at which the background should scroll.
 * @param size The size of the background entity.
 * @return A pointer to the created background entity.
 */
entity::IEntity *
Game::createBackground(uint32_t entityID, std::string texturePath,
                                    std::pair<float, float> speed,
                                    std::pair<float, float> size) {
  auto background = _coreModule->getEntityManager()->createEntity(entityID);

  _coreModule->getComponentManager()->addComponent<component::TypeComponent>(
      entityID, "background");
  _coreModule->getComponentManager()->addComponent<component::MusicComponent>(
      entityID, "app/assets/musics/testSong.wav");
  _coreModule->getComponentManager()->addComponent<component::TransformComponent>(
      entityID, std::pair<float, float>(0, 0));
  _coreModule->getComponentManager()->addComponent<component::VelocityComponent>(
      entityID, speed, speed);
  _coreModule->getComponentManager()->addComponent<component::BackgroundComponent>(
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
Game::createPlayer(uint32_t entityID, std::string texturePath,
                                std::pair<float, float> position,
                                std::pair<float, float> velocity,
                                std::pair<float, float> scale, int health) {
  auto player = _coreModule->getEntityManager()->createEntity(entityID);

  auto weapon = createWeapon(entityID, "weapon", 15, 0.5);

  _coreModule->getComponentManager()->addComponent<component::WeaponComponent>(
      entityID, weapon->getID(), true, 500);
  _coreModule->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                      "player");
  _coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
      entityID, position.first, position.second);
  auto texture =
      _coreModule->getComponentManager()->addComponent<component::TextureComponent>(
          entityID, texturePath);
  _coreModule->getComponentManager()->addComponent<component::InputComponent>(
      entityID);
  _coreModule->getComponentManager()->addComponent<component::VelocityComponent>(
      entityID, velocity);
  _coreModule->getComponentManager()->addComponent<component::TransformComponent>(
      entityID, position, scale);
  _coreModule->getComponentManager()->addComponent<component::HealthComponent>(
      entityID, health);
  _coreModule->getComponentManager()->addComponent<component::HitBoxComponent>(
      entityID, texture->getTexture().getSize().x * scale.first,
      texture->getTexture().getSize().y * scale.second);

  return player;
}

entity::IEntity *Game::createEnemy(
    uint32_t entityID, std::string texturePath,
    std::pair<float, float> position, std::pair<float, float> velocity,
    std::pair<float, float> scale, int health, int damage) {
  auto enemy = _coreModule->getEntityManager()->createEntity(entityID);

  auto weapon = createWeapon(entityID, "enemyWeapon", 15, 2);

  _coreModule->getComponentManager()->addComponent<component::WeaponComponent>(
      entityID, weapon->getID(), true, -500);
  _coreModule->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                      "enemy");
  _coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
      entityID, position.first, position.second);
  auto texture =
      _coreModule->getComponentManager()->addComponent<component::TextureComponent>(
          entityID, texturePath);
  _coreModule->getComponentManager()->addComponent<component::VelocityComponent>(
      entityID, velocity);
  _coreModule->getComponentManager()->addComponent<component::TransformComponent>(
      entityID, position, scale);

  _coreModule->getComponentManager()->addComponent<component::HealthComponent>(
      entityID, health);
  _coreModule->getComponentManager()->addComponent<component::DamageComponent>(
      entityID, damage);
  _coreModule->getComponentManager()->addComponent<component::HitBoxComponent>(
      entityID, texture->getTexture().getSize().x * scale.first,
      texture->getTexture().getSize().y * scale.second);

  return enemy;
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
void Game::init() {
  auto player = this->createPlayer(_coreModule->getEntityManager()->generateEntityID(),
                                   "app/assets/sprites/plane.png",
                                   std::pair<float, float>(100.0f, 100.0f),
                                   std::pair<float, float>(500.0f, 500.0f),
                                   std::pair<float, float>(0.25f, 0.25f), 1);

  this->createBackground(_coreModule->getEntityManager()->generateEntityID(),
                         "app/assets/images/city_background.png",
                         std::pair<float, float>(-100.0f, 0.0f),
                         std::pair<float, float>(4448.0f, 1200.0f));
  this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                    "app/assets/sprites/enemy.png",
                    std::pair<float, float>(1800.0f, 0.0f),
                    std::pair<float, float>(0.0f, 0.0f),
                    std::pair<float, float>(0.2f, 0.2f), 1, 100);

  this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                    "app/assets/sprites/enemy.png",
                    std::pair<float, float>(1800.0f, 200.0f),
                    std::pair<float, float>(0.0f, 0.0f),
                    std::pair<float, float>(0.2f, 0.2f), 1, 100);

  this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                    "app/assets/sprites/enemy.png",
                    std::pair<float, float>(1800.0f, 400.0f),
                    std::pair<float, float>(0.0f, 0.0f),
                    std::pair<float, float>(0.2f, 0.2f), 1, 100);

  this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                    "app/assets/sprites/enemy.png",
                    std::pair<float, float>(1800.0f, 600.0f),
                    std::pair<float, float>(0.0f, 0.0f),
                    std::pair<float, float>(0.2f, 0.2f), 1, 100);

  this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                    "app/assets/sprites/enemy.png",
                    std::pair<float, float>(1800.0f, 800.0f),
                    std::pair<float, float>(0.0f, 0.0f),
                    std::pair<float, float>(0.2f, 0.2f), 1, 100);

  component::ComponentManager &componentManager = *this->getComponentManager();

  entity::EntityManager &entityManager = *_coreModule->getEntityManager();

  _coreModule->getSystemManager()->addSystem(componentManager, entityManager, "audio");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                      "render");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager, "input");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                      "movement");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                      "health");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                      "collision");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                      "weapon");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                      "cooldown");
  _coreModule->getSystemManager()->addSystem(componentManager, entityManager, "game");

  _coreModule->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveLeft", sf::Keyboard::A);
  _coreModule->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveRight", sf::Keyboard::D);
  _coreModule->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveUp", sf::Keyboard::W);
  _coreModule->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveDown", sf::Keyboard::S);
  _coreModule->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("Shoot", sf::Keyboard::Space);
}