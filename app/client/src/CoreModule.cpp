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
rtype::CoreModule::CoreModule()
{
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
rtype::CoreModule::getEntityManager() const
{
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
rtype::CoreModule::getComponentManager() const
{
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
rtype::CoreModule::getSystemManager() const
{
    return this->_systemManager;
}

/**
 * @brief Runs the core module's main loop.
 *
 * This function starts a loop that continuously updates the system manager
 * with the elapsed time since the last update and the current entities from
 * the entity manager.
 */
void rtype::CoreModule::run()
{
    sf::Clock clock;
    while (1)
    {
        float deltatime = clock.restart().asSeconds();

        try
        {
            this->getSystemManager()->update(deltatime,
                                             this->getEntityManager()->getEntities());
        }
        catch (rtype::GameLoosed &e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
        catch (rtype::GameWon &e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

entity::IEntity *rtype::CoreModule::createWeapon(uint32_t parentID,
                                                 std::string type, int damage,
                                                 float cooldown)
{
    auto weapon = this->getEntityManager()->createEntity(
        this->_entityManager->generateEntityID());

    this->getComponentManager()->addComponent<component::SoundComponent>(
        weapon->getID(), "app/assets/musics/blaster.wav");
    this->getComponentManager()->addComponent<component::TypeComponent>(
        weapon->getID(), type);
    this->getComponentManager()->addComponent<component::ParentComponent>(
        weapon->getID(), parentID);
    this->getComponentManager()->addComponent<component::CooldownComponent>(
        weapon->getID(), cooldown);

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
rtype::CoreModule::createBackground(uint32_t entityID, std::string texturePath,
                                    std::pair<float, float> speed,
                                    std::pair<float, float> size)
{
    auto background = this->getEntityManager()->createEntity(entityID);

    this->getComponentManager()->addComponent<component::TypeComponent>(
        entityID, "background");
    this->getComponentManager()->addComponent<component::MusicComponent>(
        entityID, "app/assets/musics/testSong.wav");
    this->getComponentManager()->addComponent<component::TransformComponent>(
        entityID, std::pair<float, float>(0, 0));
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
                                std::pair<float, float> position,
                                std::pair<float, float> velocity,
                                std::pair<float, float> scale, int health)
{
    auto player = this->getEntityManager()->createEntity(entityID);

    auto weapon = this->createWeapon(entityID, "weapon", 15, 0.5);

    this->getComponentManager()->addComponent<component::WeaponComponent>(
        entityID, weapon->getID(), true, 500);
    this->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                        "player");
    this->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second);
    auto texture =
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
    this->getComponentManager()->addComponent<component::HitBoxComponent>(
        entityID, texture->getTexture().getSize().x * scale.first,
        texture->getTexture().getSize().y * scale.second);

    return player;
}

entity::IEntity *rtype::CoreModule::createEnemy(
    uint32_t entityID, std::string texturePath,
    std::pair<float, float> position, std::pair<float, float> velocity,
    std::pair<float, float> scale, int health, int damage)
{
    auto enemy = this->getEntityManager()->createEntity(entityID);

    auto weapon = this->createWeapon(entityID, "enemyWeapon", 15, 2);

    this->getComponentManager()->addComponent<component::WeaponComponent>(
        entityID, weapon->getID(), true, -500);
    this->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                        "enemy");
    this->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second);
    auto texture =
        this->getComponentManager()->addComponent<component::TextureComponent>(
            entityID, texturePath);
    this->getComponentManager()->addComponent<component::VelocityComponent>(
        entityID, velocity);
    this->getComponentManager()->addComponent<component::TransformComponent>(
        entityID, position, scale);

    this->getComponentManager()->addComponent<component::HealthComponent>(
        entityID, health);
    this->getComponentManager()->addComponent<component::DamageComponent>(
        entityID, damage);
    this->getComponentManager()->addComponent<component::HitBoxComponent>(
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
void rtype::CoreModule::init()
{
    auto player = this->createPlayer(this->getEntityManager()->generateEntityID(),
                                     "app/assets/sprites/plane.png",
                                     std::pair<float, float>(100.0f, 100.0f),
                                     std::pair<float, float>(500.0f, 500.0f),
                                     std::pair<float, float>(0.25f, 0.25f), 1);

    this->createBackground(this->getEntityManager()->generateEntityID(),
                           "app/assets/images/city_background.png",
                           std::pair<float, float>(100.0f, 0.0f),
                           std::pair<float, float>(4448.0f, 1200.0f));
    this->createEnemy(this->getEntityManager()->generateEntityID(),
                      "app/assets/sprites/enemy.png",
                      std::pair<float, float>(1800.0f, 0.0f),
                      std::pair<float, float>(0.0f, 0.0f),
                      std::pair<float, float>(0.2f, 0.2f), 1, 100);

    this->createEnemy(this->getEntityManager()->generateEntityID(),
                      "app/assets/sprites/enemy.png",
                      std::pair<float, float>(1800.0f, 200.0f),
                      std::pair<float, float>(0.0f, 0.0f),
                      std::pair<float, float>(0.2f, 0.2f), 1, 100);

    this->createEnemy(this->getEntityManager()->generateEntityID(),
                      "app/assets/sprites/enemy.png",
                      std::pair<float, float>(1800.0f, 400.0f),
                      std::pair<float, float>(0.0f, 0.0f),
                      std::pair<float, float>(0.2f, 0.2f), 1, 100);

    this->createEnemy(this->getEntityManager()->generateEntityID(),
                      "app/assets/sprites/enemy.png",
                      std::pair<float, float>(1800.0f, 600.0f),
                      std::pair<float, float>(0.0f, 0.0f),
                      std::pair<float, float>(0.2f, 0.2f), 1, 100);

    this->createEnemy(this->getEntityManager()->generateEntityID(),
                      "app/assets/sprites/enemy.png",
                      std::pair<float, float>(1800.0f, 800.0f),
                      std::pair<float, float>(0.0f, 0.0f),
                      std::pair<float, float>(0.2f, 0.2f), 1, 100);

    component::ComponentManager &componentManager = *this->getComponentManager();

    entity::EntityManager &entityManager = *this->getEntityManager();

    this->getSystemManager()->addSystem(componentManager, entityManager, "audio");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "render");
    this->getSystemManager()->addSystem(componentManager, entityManager, "input");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "movement");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "background");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "health");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "collision");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "weapon");
    this->getSystemManager()->addSystem(componentManager, entityManager,
                                        "cooldown");
    this->getSystemManager()->addSystem(componentManager, entityManager, "game");

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
    this->getComponentManager()
        ->getComponent<component::InputComponent>(0)
        ->bindAction("Shoot", sf::Keyboard::Space);
}