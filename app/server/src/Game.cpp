/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "include/Game.hpp"

Game::Game(std::shared_ptr<rtype::CoreModule> coreModule) : _coreModule(coreModule)
{
}

Game::~Game()
{
}

entity::IEntity *Game::createWeapon(uint32_t parentID,
                                    component::Type type, int damage,
                                    float cooldown)
{
    auto weapon = _coreModule->getEntityManager()->createEntity(
        _coreModule->getEntityManager()->generateEntityID());

    // _coreModule->getComponentManager()->addComponent<component::SoundComponent>(
    //     weapon->getID(), "app/assets/musics/blaster.wav");
    _coreModule->getComponentManager()->addComponent<component::TypeComponent>(
        weapon->getID(), type);
    _coreModule->getComponentManager()->addComponent<component::ParentComponent>(
        weapon->getID(), parentID);
    _coreModule->getComponentManager()->addComponent<component::CooldownComponent>(
        weapon->getID(), cooldown);
    _coreModule->getComponentManager()->addComponent<component::DamageComponent>(
        weapon->getID(), damage);

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
entity::IEntity *Game::createBackground(std::string texturePath,
                                        std::pair<float, float> speed,
                                        std::pair<float, float> size)
{
    entity::IEntity *background1 = _coreModule->getEntityManager()->createEntity(
        _coreModule->getEntityManager()->generateEntityID());

    entity::IEntity *background2 = _coreModule->getEntityManager()->createEntity(
        _coreModule->getEntityManager()->generateEntityID());

    _coreModule->getComponentManager()->addComponent<component::TypeComponent>(
        background1->getID(), component::Type::BACKGROUND);
    _coreModule->getComponentManager()->addComponent<component::MusicComponent>(
        background1->getID(), "app/assets/musics/testSong.wav");
    _coreModule->getComponentManager()->addComponent<component::TransformComponent>(
        background1->getID(), std::pair<float, float>(0, 0));
    _coreModule->getComponentManager()->addComponent<component::VelocityComponent>(
        background1->getID(), speed, speed);
    _coreModule->getComponentManager()->addComponent<component::TextureComponent>(
        background1->getID(), texturePath);
    _coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
        background1->getID(), 0, 0);
    _coreModule->getComponentManager()->addComponent<component::SizeComponent>(
        background1->getID(), size);

    _coreModule->getComponentManager()->addComponent<component::TypeComponent>(
        background2->getID(), component::Type::BACKGROUND);
    _coreModule->getComponentManager()->addComponent<component::TransformComponent>(
        background2->getID(), std::pair<float, float>(size.first - 20, 0));
    _coreModule->getComponentManager()->addComponent<component::VelocityComponent>(
        background2->getID(), speed, speed);
    _coreModule->getComponentManager()->addComponent<component::TextureComponent>(
        background2->getID(), texturePath);
    _coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
        background2->getID(), size.first, 0);
    _coreModule->getComponentManager()->addComponent<component::SizeComponent>(
        background2->getID(), size);

    return background1;
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
                   std::pair<float, float> scale, int health, int numClient)
{
    auto player = _coreModule->getEntityManager()->createEntity(entityID);

    auto weapon = createWeapon(entityID, component::Type::WEAPON, 50, 0.5);

    _coreModule->getComponentManager()->addComponent<component::WeaponComponent>(
        entityID, weapon->getID(), false, 500);
    _coreModule->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                               component::Type::PLAYER);
    _coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second);
    auto texture =
        _coreModule->getComponentManager()->addComponent<component::TextureComponent>(
            entityID, texturePath);
    _coreModule->getComponentManager()->addComponent<component::InputComponent>(
        entityID, numClient);
    _coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction("MoveLeft", sf::Keyboard::Q);
    _coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction("MoveRight", sf::Keyboard::D);
    _coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction("MoveUp", sf::Keyboard::Z);
    _coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction("MoveDown", sf::Keyboard::S);
    _coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction("Shoot", sf::Keyboard::Space);
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
    std::pair<float, float> scale, int health, int damage)
{
    auto enemy = _coreModule->getEntityManager()->createEntity(entityID);

    auto weapon = createWeapon(entityID, component::Type::WEAPON, damage, 2);

    _coreModule->getComponentManager()->addComponent<component::WeaponComponent>(
        entityID, weapon->getID(), true, -500);
    _coreModule->getComponentManager()->addComponent<component::TypeComponent>(entityID, component::Type::ENEMY);
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
    _coreModule->getComponentManager()->addComponent<component::HitBoxComponent>(
        entityID, texture->getTexture().getSize().x * scale.first,
        texture->getTexture().getSize().y * scale.second);
    _coreModule->getComponentManager()->addComponent<component::AIComponent>(
        entityID, component::AIType::SINUSOIDAL);

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
void Game::init()
{
    this->createBackground("app/assets/images/city_background.png",
                           std::pair<float, float>(-100.0f, 0.0f),
                           std::pair<float, float>(4448.0f, 1200.0f));
    this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                      "app/assets/sprites/enemy.png",
                      std::pair<float, float>(1800.0f, 0.0f),
                      std::pair<float, float>(-200.0f, 0.0f),
                      std::pair<float, float>(0.2f, 0.2f), 100, 100);

    component::ComponentManager &componentManager = *_coreModule->getComponentManager();

    entity::EntityManager &entityManager = *_coreModule->getEntityManager();

    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "movement");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "server");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "cooldown");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "weapon");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "ai");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "collision");
    // _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
    //                                            "health");
    // _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
    //                                            "game");
    this->_spawnInterval = 5;
    this->_waveNumber = 10;
}

void Game::handdleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived)
{
    std::string msg = msgReceived.front().first;
    size_t id = msgReceived.front().second.first;
    int numClient = msgReceived.front().second.second;
    msgReceived.erase(msgReceived.begin());
    if (msg == "clientConnection")
    {
        entity::IEntity *entity = createPlayer(_coreModule->getEntityManager()->generateEntityID(), "app/assets/sprites/plane.png",
                                               std::pair<float, float>(100.0f, 100.0f),
                                               std::pair<float, float>(500.0f, 500.0f),
                                               std::pair<float, float>(0.10f, 0.10f), 100, numClient);
        _players[numClient] = entity;
        std::cout << "Client connected : " << id << std::endl;
    }
    if (msg == "clientDisconnection")
    {
        std::cout << "Client disconnected : " << numClient << std::endl;
        if (_players.find(numClient) != _players.end())
        {
            _players[numClient]->setCommunication(entity::EntityCommunication::DELETE);
            _players.erase(numClient);
        }
    }
    // std::cout << "numClient: " << numClient << std::endl;
    if (_players.find(numClient) == _players.end()) {
        std::cout << "Player not found" << std::endl;
        return;
    }
    if (_players[numClient]->getID() != id) {
        std::cout << "Player ID not matching" << std::endl;
        return;
    }
    if (msg == "moveUp" || msg == "moveDown" || msg == "moveLeft" || msg == "moveRight")
        moveEntity(msg, id);
    if (msg == "shoot")
        shootEntity(id);
}

void Game::shootEntity(size_t id)
{
    if (_coreModule->getComponentManager()->getComponent<component::WeaponComponent>(id))
    {
        component::WeaponComponent *weaponComponent = _coreModule->getComponentManager()->getComponent<component::WeaponComponent>(id);
        weaponComponent->setIsFiring(true);
    }
}

void Game::moveEntity(std::string msg, size_t id)
{
    if (_coreModule->getComponentManager()->getComponent<component::VelocityComponent>(id))
    {
        component::VelocityComponent *velocityComponent = _coreModule->getComponentManager()->getComponent<component::VelocityComponent>(id);
        if (msg == "moveUp")
            velocityComponent->setActualVelocityY(-velocityComponent->getVelocity().second);
        if (msg == "moveDown")
            velocityComponent->setActualVelocityY(velocityComponent->getVelocity().second);
        if (msg == "moveLeft")
            velocityComponent->setActualVelocityX(-velocityComponent->getVelocity().first);
        if (msg == "moveRight")
            velocityComponent->setActualVelocityX(velocityComponent->getVelocity().first);
        velocityComponent->setCommunication(component::ComponentCommunication::UPDATE);
    }
}

void Game::resetInput()
{
    // get All entities with input component
    std::vector<std::shared_ptr<entity::IEntity>> entities = _coreModule->getEntityManager()->getEntities();

    for (auto &entity : entities)
    {
        if (_coreModule->getComponentManager()->getComponent<component::InputComponent>(entity->getID()))
        {
            if (_coreModule->getComponentManager()->getComponent<component::VelocityComponent>(entity->getID()))
            {
                component::VelocityComponent *velocityComponent = _coreModule->getComponentManager()->getComponent<component::VelocityComponent>(entity->getID());
                if ((velocityComponent->getActualVelocity().first != 0 || velocityComponent->getActualVelocity().second != 0) && inputClock.getElapsedTime().asSeconds() > 0.1)
                {
                    velocityComponent->setActualVelocityX(0);
                    velocityComponent->setActualVelocityY(0);
                    velocityComponent->setCommunication(component::ComponentCommunication::UPDATE);
                    inputClock.restart();
                }
            }
        }
    }
}

float getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1080);
    return dis(gen);
}

void Game::run()
{
    inputClock.restart();
    waveClock.restart();
    while (1)
    {
        _coreModule->update();
        if (_waveNumber != 0 && waveClock.getElapsedTime().asSeconds() > _spawnInterval)
        {
            float randomPosition = getRandomPosition();

            this->createEnemy(_coreModule->getEntityManager()->generateEntityID(),
                              "app/assets/sprites/enemy.png",
                              std::pair<float, float>(1920.0f, randomPosition),
                              std::pair<float, float>(-200.0f, 0.0f),
                              std::pair<float, float>(0.2f, 0.2f), 100, 100);
            _waveNumber--;
            waveClock.restart();
        }
        if (!_coreModule->msgReceived.empty())
        {
            // std::cout << "msgReceivedSize: " << _coreModule->msgReceived.size() << std::endl;
            handdleReceivedMessage(_coreModule->msgReceived);
        }
        else
        {
            resetInput();
        }
    }
}