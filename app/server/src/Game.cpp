/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "include/Game.hpp"

Game::Game(std::shared_ptr<rtype::RtypeEngine> coreModule) : _engine(coreModule)
{
}

Game::~Game()
{
}

float getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1080);
    return dis(gen);
}

entity::IEntity *Game::createWeapon(uint32_t parentID,
                                    Type type, int damage,
                                    float cooldown)
{
    auto weapon = _engine->getEntityManager()->createEntity(
        _engine->getEntityManager()->generateEntityID(), -1);

    // _engine->getComponentManager()->addComponent<component::SoundComponent>(
    //     weapon->getID(), "app/assets/musics/blaster.wav");
    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        weapon->getID(), type);
    _engine->getComponentManager()->addComponent<component::ParentComponent>(
        weapon->getID(), parentID);
    _engine->getComponentManager()->addComponent<component::CooldownComponent>(
        weapon->getID(), cooldown);
    _engine->getComponentManager()->addComponent<component::DamageComponent>(
        weapon->getID(), damage);

    return weapon;
}

/**
 * @brief Creates and initializes background entities for the game.
 *
 * This function reads the background configuration from a JSON file, including
 * the texture path, velocity, and size. It then creates two background entities
 * and adds various components to them, such as TypeComponent, MusicComponent,
 * TransformComponent, VelocityComponent, TextureComponent, SpriteComponent, and
 * SizeComponent. The second background entity is positioned to the right of the
 * first one to create a seamless scrolling effect.
 *
 * @return A pointer to the first background entity created.
 */
entity::IEntity *Game::createBackground()
{
    nlohmann::json config = this->getConfig();

    if (config.contains("background") == false)
        return nullptr;

    std::string texturePath = config["background"]["path"];
    std::pair<float, float> speed = std::pair<float, float>(config["background"]["velocity"]["x"], config["background"]["velocity"]["y"]);
    std::pair<float, float> size = std::pair<float, float>(config["background"]["size"]["width"], config["background"]["size"]["height"]);

    entity::IEntity *background1 = _engine->getEntityManager()->createEntity(
        _engine->getEntityManager()->generateEntityID(), -1);

    entity::IEntity *background2 = _engine->getEntityManager()->createEntity(
        _engine->getEntityManager()->generateEntityID(), -1);

    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        background1->getID(), Type::BACKGROUND);
    _engine->getComponentManager()->addComponent<component::MusicComponent>(
        background1->getID(), "app/assets/musics/testSong.wav");
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        background1->getID(), std::pair<float, float>(0, 0));
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        background1->getID(), speed, speed);
    _engine->getComponentManager()->addComponent<component::TextureComponent>(
        background1->getID(), texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        background1->getID(), 0, 0, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SizeComponent>(
        background1->getID(), size);

    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        background2->getID(), Type::BACKGROUND);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        background2->getID(), std::pair<float, float>(size.first - 20, 0));
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        background2->getID(), speed, speed);
    _engine->getComponentManager()->addComponent<component::TextureComponent>(
        background2->getID(), texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        background2->getID(), size.first, 0, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SizeComponent>(
        background2->getID(), size);

    return background1;
}

void Game::BindInputScript(entity::IEntity *entity)
{
    uint32_t entityID = entity->getID();

    _engine->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction(Action::MOVE_LEFT, KeyBoard::Q);
    _engine->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction(Action::MOVE_RIGHT, KeyBoard::D);
    _engine->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction(Action::MOVE_UP, KeyBoard::Z);
    _engine->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction(Action::MOVE_DOWN, KeyBoard::S);
    _engine->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction(Action::SHOOT, KeyBoard::Space);
    _engine->getComponentManager()
        ->getComponent<component::InputComponent>(entityID)
        ->bindAction(Action::MENU, KeyBoard::escape);
}

/**
 * @brief Creates a player entity with the specified client number.
 *
 * This function initializes a player entity with various components such as
 * weapon, sprite, input, velocity, transform, health, and hitbox. The configuration
 * for the player is loaded from a JSON file.
 *
 * @param numClient The client number associated with the player.
 * @return A pointer to the created player entity.
 */
entity::IEntity *Game::createPlayer(int numClient)
{
    nlohmann::json config = this->getConfig();
    uint32_t entityID = _engine->getEntityManager()->generateEntityID();

    if (config.contains("player") == false)
        return nullptr;

    std::string texturePath = config["player"]["path"];
    std::pair<float, float> position = std::pair<float, float>(config["player"]["position"]["x"], config["player"]["position"]["y"]);
    std::pair<float, float> velocity = std::pair<float, float>(config["player"]["velocity"]["x"], config["player"]["velocity"]["y"]);
    std::pair<float, float> scale = std::pair<float, float>(config["player"]["scale"]["x"], config["player"]["scale"]["y"]);
    int health = config["player"]["health"];

    int weaponDamage = config["player"]["weapon"]["damage"];
    float weaponCooldown = config["player"]["weapon"]["cooldown"];

    entity::IEntity *player = _engine->getEntityManager()->createEntity(entityID, -1);

    entity::IEntity *weapon = createWeapon(entityID, Type::WEAPON, weaponDamage, weaponCooldown);

    _engine->getComponentManager()->addComponent<component::WeaponComponent>(
        entityID, weapon->getID(), false, 500);
    _engine->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                               Type::PLAYER);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second, _engine->_graphic);
    component::TextureComponent *texture =
        _engine->getComponentManager()->addComponent<component::TextureComponent>(
            entityID, texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::InputComponent>(
        entityID, numClient);
    BindInputScript(player);
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        entityID, velocity);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        entityID, position, scale);
    _engine->getComponentManager()->addComponent<component::HealthComponent>(
        entityID, health);
    _engine->getComponentManager()->addComponent<component::HitBoxComponent>(
        entityID, _engine->_graphic->getTextureSize(texture->getTexture()).first * scale.first,
        _engine->_graphic->getTextureSize(texture->getTexture()).second * scale.second);

    return player;
}

/**
 * @brief Creates an enemy entity based on the configuration.
 *
 * This function reads the enemy configuration from a JSON object, generates a new entity ID,
 * and creates an enemy entity with various components such as AI, weapon, sprite, texture,
 * velocity, transform, health, and hitbox. The position of the enemy can be random or specified
 * in the configuration. The AI type can also be random or specified.
 *
 * @return entity::IEntity* Pointer to the created enemy entity.
 */
entity::IEntity *Game::createEnemy()
{
    nlohmann::json config = this->getConfig();

    if (config.contains("enemy") == false)
        return nullptr;

    std::string texturePath = config["enemy"]["path"];
    int damage = config["enemy"]["damage"];
    std::pair<float, float> velocity = std::pair<float, float>(config["enemy"]["velocity"]["x"], config["enemy"]["velocity"]["y"]);
    std::pair<float, float> scale = std::pair<float, float>(config["enemy"]["scale"]["x"], config["enemy"]["scale"]["y"]);
    auto positionInput = config["enemy"]["position"];
    int health = config["enemy"]["health"];
    std::pair<float, float> position;
    std::string iaType = config["enemy"]["iaType"];

    if (positionInput["x"] == "random")
        position.first = getRandomPosition();
    else
        position.first = positionInput["x"];
    if (positionInput["y"] == "random")
        position.second = getRandomPosition();
    else
        position.second = positionInput["y"];

    uint32_t entityID = _engine->getEntityManager()->generateEntityID();
    entity::IEntity *enemy = _engine->getEntityManager()->createEntity(entityID, -1);
    entity::IEntity *weapon = createWeapon(entityID, Type::WEAPON, damage, 2);

    if (iaType == "random")
    {
        int random = rand() % 3;
        if (random == 0)
            _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::LINEAR);
        if (random == 1)
            _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::SINUSOIDAL);
        if (random == 2)
            _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::CIRCULAR);
    }
    else if (iaType == "linear")
        _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::LINEAR);
    else if (iaType == "sinusoidal")
        _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::SINUSOIDAL);
    else if (iaType == "circular")
        _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::CIRCULAR);
    else
        _engine->getComponentManager()->addComponent<component::AIComponent>(entityID, AIType::UNKNOWN);

    _engine->getComponentManager()->addComponent<component::WeaponComponent>(
        entityID, weapon->getID(), true, -500);
    _engine->getComponentManager()->addComponent<component::TypeComponent>(entityID, Type::ENEMY);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second, _engine->_graphic);
    component::TextureComponent *texture =
        _engine->getComponentManager()->addComponent<component::TextureComponent>(
            entityID, texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        entityID, velocity);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        entityID, position, scale);

    _engine->getComponentManager()->addComponent<component::HealthComponent>(
        entityID, health);
    _engine->getComponentManager()->addComponent<component::HitBoxComponent>(
        entityID, _engine->_graphic->getTextureSize(texture->getTexture()).first * scale.first,
        _engine->_graphic->getTextureSize(texture->getTexture()).second * scale.second);

    return enemy;
}

entity::IEntity *Game::createButton(uint32_t entityID, RColor color, std::pair<float, float> position, std::pair<float, float> size, Action action, int numClient, std::string text)
{
    entity::IEntity *button = _engine->getEntityManager()->createEntity(entityID, numClient);

    _engine->getComponentManager()->addComponent<component::RectangleShapeComponent>(entityID, position, size, color, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(entityID, position, std::pair<float, float>(1, 1));
    _engine->getComponentManager()->addComponent<component::OnClickComponent>(entityID, action, numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(entityID, position, text, 50, RColor{25, 25, 25, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);

    return button;
}

void Game::createMenu(int numClient)
{
    entity::IEntity *buttonPlay = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(860.0f, 700.0f), std::pair<float, float>(70.0f, 200.0f), Action::PLAY, numClient, "Play");
    entity::IEntity *buttonProtanopia = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 20.0f), std::pair<float, float>(70.0f, 300.0f), Action::PROTANOPIA, numClient, "Protanopia");
    entity::IEntity *buttonDeuteranopia = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 110.0f), std::pair<float, float>(70.0f, 300.0f), Action::DEUTERANOPIA, numClient, "Deuteranopia");
    entity::IEntity *buttonTritanopia = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 200.0f), std::pair<float, float>(70.0f, 300.0f), Action::TRITANOPIA, numClient, "Tritanopia");
    entity::IEntity *buttonClearFilter = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 290.0f), std::pair<float, float>(70.0f, 300.0f), Action::CLEARFILTER, numClient, "Clear Filter");
    buttonPlay->setSceneStatus(Scene::MENU);
    buttonProtanopia->setSceneStatus(Scene::MENU);
    buttonDeuteranopia->setSceneStatus(Scene::MENU);
    buttonTritanopia->setSceneStatus(Scene::MENU);
    buttonClearFilter->setSceneStatus(Scene::MENU);
}

entity::IEntity *Game::createStructure(uint32_t entityID, std::string texturePath,
                                       std::pair<float, float> position,
                                       std::pair<float, float> scale, int health)
{
    entity::IEntity *structure = _engine->getEntityManager()->createEntity(entityID, -1);

    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        entityID, Type::STRUCTURE);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second, _engine->_graphic);
    component::TextureComponent *texture =
        _engine->getComponentManager()->addComponent<component::TextureComponent>(
            entityID, texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        entityID, position, scale);
    _engine->getComponentManager()->addComponent<component::HitBoxComponent>(
        entityID, _engine->_graphic->getTextureSize(texture->getTexture()).first * scale.first,
        _engine->_graphic->getTextureSize(texture->getTexture()).second * scale.second);
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        entityID, std::pair<float, float>(-200.0f, 0.0f), std::pair<float, float>(-200.0f, 0.0f));
    _engine->getComponentManager()->addComponent<component::HealthComponent>(
        entityID, health);

    return structure;
}

nlohmann::json Game::fillConfigJson(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + path);

    nlohmann::json json;

    file >> json;

    return json;
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
  ECS_system::StringCom stringCom;
  stringCom.texturePath[TexturePath::Player] = "app/assets/sprites/plane.png";
  stringCom.texturePath[TexturePath::Enemy] = "app/assets/sprites/enemy.png";
  stringCom.texturePath[TexturePath::Background] = "app/assets/images/city_background.png";
  stringCom.texturePath[TexturePath::Bullet] = "app/assets/sprites/projectile.gif";
  stringCom.textFont[TextFont::Arial] = "app/assets/fonts/arial.ttf";
  stringCom.textString[TextString::Play] = "Play";
  stringCom.textString[TextString::Protanopia] = "Protanopia";
  stringCom.textString[TextString::Deuteranopia] = "Deuteranopia";
  stringCom.textString[TextString::Tritanopia] = "Tritanopia";
  stringCom.textString[TextString::ClearFilter] = "Clear Filter";

    try
    {
        this->setConfig(this->fillConfigJson("configs/config1.json"));

        this->createBackground();

        this->createStructure(_engine->getEntityManager()->generateEntityID(),
                              "app/assets/sprites/block.png",
                              std::pair<float, float>(1920.0f, 0.0f),
                              std::pair<float, float>(0.5f, 0.5f), 50);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    component::ComponentManager &componentManager = *_engine->getComponentManager();

    entity::EntityManager &entityManager = *_engine->getEntityManager();

    _engine->getSystemManager()->addSystem(componentManager, entityManager,
                                               "movement", _engine->_graphic, stringCom);
    _engine->getSystemManager()->addSystem(componentManager, entityManager,
                                               "server", _engine->_graphic, stringCom);
    _engine->getSystemManager()->addSystem(componentManager, entityManager,
                                               "cooldown", _engine->_graphic, stringCom);
    _engine->getSystemManager()->addSystem(componentManager, entityManager,
                                               "weapon", _engine->_graphic, stringCom);
    _engine->getSystemManager()->addSystem(componentManager, entityManager,
                                               "ai", _engine->_graphic, stringCom);
    _engine->getSystemManager()->addSystem(componentManager, entityManager,
                                               "collision", _engine->_graphic, stringCom);
    // _engine->getSystemManager()->addSystem(componentManager, entityManager,
    //                                            "health", _engine->_graphic);
    // _engine->getSystemManager()->addSystem(componentManager, entityManager,
    //                                            "game", _engine->_graphic);

    int waveInterval = this->getConfig()["waveInterval"];
    int waveNumber = this->getConfig()["waveNumber"];
    this->_waveInterval = waveInterval;
    this->_waveNumber = waveNumber;
}

entity::IEntity *Game::addFilter(std::string filter, int numClient)
{
    entity::IEntity *filterEntity = _engine->getEntityManager()->createEntity(_engine->getEntityManager()->generateEntityID(), numClient);
    if (filter == "protanopia")
        _engine->getComponentManager()->addComponent<component::RectangleShapeComponent>(filterEntity->getID(), std::pair<float, float>(0, 0), std::pair<float, float>(1080, 1920), RColor{56, 181, 0, 25}, _engine->_graphic);
    if (filter == "deuteranopia")
        _engine->getComponentManager()->addComponent<component::RectangleShapeComponent>(filterEntity->getID(), std::pair<float, float>(0, 0), std::pair<float, float>(1080, 1920), RColor{119, 119, 0, 25}, _engine->_graphic);
    if (filter == "tritanopia")
        _engine->getComponentManager()->addComponent<component::RectangleShapeComponent>(filterEntity->getID(), std::pair<float, float>(0, 0), std::pair<float, float>(1080, 1920), RColor{255, 127, 0, 25}, _engine->_graphic);
    filterEntity->setSceneStatus(Scene::ALL);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(filterEntity->getID(), std::pair<float, float>(0, 0), std::pair<float, float>(1, 1));
    _engine->getComponentManager()->addComponent<component::TypeComponent>(filterEntity->getID(), Type::FILTER);
    std::cout << "Filter added with id: " << filterEntity->getID() << "and a numClient of: " << numClient << std::endl;
    return filterEntity;
}

void Game::handdleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived)
{
    std::string msg = msgReceived.front().first;
    size_t id = msgReceived.front().second.first;
    int numClient = msgReceived.front().second.second;
    msgReceived.erase(msgReceived.begin());
    if (msg == "clientConnection")
    {

        _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::MENU, numClient));
        _playersScenes[numClient] = Scene::MENU;
        createMenu(numClient);
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
    if (msg == "play") {
        if (_playersScenes[numClient] == Scene::GAME)
            return;
        if (_players.find(numClient) == _players.end()) {
            entity::IEntity *entity = createPlayer(numClient);
            _players[numClient] = entity;
        }
        _playersScenes[numClient] = Scene::GAME;
        _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::GAME, numClient));
    }
    if (msg == "protanopia")
    {
        if (_playersFilters.find(numClient) != _playersFilters.end())
        {
            if (_playersFilters[numClient].second == "protanopia")
                return;
            _playersFilters[numClient].first->setCommunication(entity::EntityCommunication::DELETE);
            _playersFilters.erase(numClient);
        }
        _playersFilters[numClient] = std::pair<entity::IEntity *, std::string>(addFilter("protanopia", numClient), "protanopia");
    }
    if (msg == "deuteranopia")
    {
        if (_playersFilters.find(numClient) != _playersFilters.end())
        {
            if (_playersFilters[numClient].second == "deuteranopia")
                return;
            _playersFilters[numClient].first->setCommunication(entity::EntityCommunication::DELETE);
            _playersFilters.erase(numClient);
        }
        _playersFilters[numClient] = std::pair<entity::IEntity *, std::string>(addFilter("deuteranopia", numClient), "deuteranopia");
    }
    if (msg == "tritanopia")
    {
        if (_playersFilters.find(numClient) != _playersFilters.end())
        {
            if (_playersFilters[numClient].second == "tritanopia")
                return;
            _playersFilters[numClient].first->setCommunication(entity::EntityCommunication::DELETE);
            _playersFilters.erase(numClient);
        }
        _playersFilters[numClient] = std::pair<entity::IEntity *, std::string>(addFilter("tritanopia", numClient), "tritanopia");
    }
    if (msg == "clearFilter")
    {
        if (_playersFilters.find(numClient) != _playersFilters.end())
        {
            _playersFilters[numClient].first->setCommunication(entity::EntityCommunication::DELETE);
            _playersFilters.erase(numClient);
        }
    }
    if (msg == "menu")
    {
        if (_playersScenes[numClient] == Scene::MENU)
            return;
        _playersScenes[numClient] = Scene::MENU;
        _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::MENU, numClient));
    }
    // std::cout << "numClient: " << numClient << std::endl;
    if (_players.find(numClient) == _players.end())
    {
        // std::cout << "Player not found" << std::endl;
        return;
    }
    if (_players[numClient]->getID() != id)
    {
        // std::cout << "Player ID not matching" << std::endl;
        return;
    }
    if (msg == "moveUp" || msg == "moveDown" || msg == "moveLeft" || msg == "moveRight")
        moveEntity(msg, id);
    if (msg == "shoot")
        shootEntity(id);
}

void Game::shootEntity(size_t id)
{
    if (_engine->getComponentManager()->getComponent<component::WeaponComponent>(id))
    {
        component::WeaponComponent *weaponComponent = _engine->getComponentManager()->getComponent<component::WeaponComponent>(id);
        weaponComponent->setIsFiring(true);
    }
}

void Game::moveEntity(std::string msg, size_t id)
{
    if (_engine->getComponentManager()->getComponent<component::VelocityComponent>(id))
    {
        component::VelocityComponent *velocityComponent = _engine->getComponentManager()->getComponent<component::VelocityComponent>(id);
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
    std::vector<std::shared_ptr<entity::IEntity>> entities = _engine->getEntityManager()->getEntities();

    for (auto &entity : entities)
    {
        if (_engine->getComponentManager()->getComponent<component::InputComponent>(entity->getID()))
        {
            if (_engine->getComponentManager()->getComponent<component::VelocityComponent>(entity->getID()))
            {
                component::VelocityComponent *velocityComponent = _engine->getComponentManager()->getComponent<component::VelocityComponent>(entity->getID());
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

void Game::run()
{
    inputClock.restart();
    waveClock.restart();
    while (1)
    {
        _engine->update();
        if (_waveNumber != 0 && waveClock.getElapsedTime().asSeconds() > _waveInterval)
        {
            this->createEnemy();
            _waveNumber--;
            waveClock.restart();
        }
        if (!_engine->msgReceived.empty())
        {
            // std::cout << "msgReceivedSize: " << _engine->msgReceived.size() << std::endl;
            handdleReceivedMessage(_engine->msgReceived);
        }
        else
        {
            resetInput();
        }
    }
}