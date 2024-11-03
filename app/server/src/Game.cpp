/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "include/Game.hpp"

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game with the provided core module, setting the initial state
 * of the game to not started, structure not created, running, with wave number
 * and wave interval set to 0.
 *
 * @param coreModule A shared pointer to the RtypeEngine core module.
 */
Game::Game(std::shared_ptr<rtype::RtypeEngine> coreModule) : _engine(coreModule)
{
    _isStarted = false;
    _structureCreated = false;
    _isRunning = true;
    _waveNumber = 0;
    _waveInterval = 0;
}

/**
 * @brief Destructor for the Game class.
 *
 * This destructor is responsible for cleaning up any resources
 * that the Game object may have acquired during its lifetime.
 */
Game::~Game()
{
}

/**
 * @brief Generates a random RColor with random RGB values and full opacity.
 *
 * This function creates an RColor object with each of the red, green, and blue
 * components set to a random value between 0 and 255. The alpha component is
 * set to 255, making the color fully opaque.
 *
 * @return RColor A randomly generated color with random RGB values and full opacity.
 */
RColor Game::getRandomRColor()
{
    RColor color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    color.a = 255;

    return color;
}

/**
 * @brief Generates a random floating-point number representing a position.
 *
 * This function uses a random device to seed a Mersenne Twister engine, which
 * generates a random floating-point number uniformly distributed between 0 and 1080.
 *
 * @return A random float between 0 and 1080.
 */
float getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1080);
    return dis(gen);
}

/**
 * @brief Creates a weapon entity with specified properties.
 *
 * This function creates a weapon entity and attaches various components to it,
 * such as sound, type, parent, cooldown, and damage components.
 *
 * @param parentID The ID of the parent entity.
 * @param weapon A JSON object containing the weapon properties.
 * @return entity::IEntity* A pointer to the created weapon entity.
 */
entity::IEntity *Game::createWeapon(uint32_t parentID, nlohmann::json &weapon)
{
    int damage = weapon["damage"];
    float cooldown = weapon["cooldown"];

    auto weaponEntity = _engine->getEntityManager()->createEntity(
        _engine->getEntityManager()->generateEntityID(), -1);

    _engine->getComponentManager()->addComponent<component::SoundComponent>(
        weaponEntity->getID(), "app/assets/musics/blaster.wav", _engine->_audio);
    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        weaponEntity->getID(), Type::WEAPON);
    _engine->getComponentManager()->addComponent<component::ParentComponent>(
        weaponEntity->getID(), parentID);
    _engine->getComponentManager()->addComponent<component::CooldownComponent>(
        weaponEntity->getID(), cooldown);
    _engine->getComponentManager()->addComponent<component::DamageComponent>(
        weaponEntity->getID(), damage);

    return weaponEntity;
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

    if (_config.contains("background") == false)
        return nullptr;

    std::string texturePath = _config["background"]["path"];
    std::pair<float, float> speed = std::pair<float, float>(_config["background"]["velocity"]["x"], _config["background"]["velocity"]["y"]);
    std::pair<float, float> size = std::pair<float, float>(_config["background"]["size"]["width"], _config["background"]["size"]["height"]);

    entity::IEntity *background1 = _engine->getEntityManager()->createEntity(
        _engine->getEntityManager()->generateEntityID(), -1);

    entity::IEntity *background2 = _engine->getEntityManager()->createEntity(
        _engine->getEntityManager()->generateEntityID(), -1);

    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        background1->getID(), Type::BACKGROUND);
    _engine->getComponentManager()->addComponent<component::MusicComponent>(
        background1->getID(), "app/assets/musics/dancin.ogg", _engine->_audio);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        background1->getID(), std::pair<float, float>(0, 0));
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        background1->getID(), speed, speed);
    _engine->getComponentManager()->addComponent<component::TextureComponent>(
        background1->getID(), texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        background1->getID(), 0, 0, RColor{255, 255, 255, 255}, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SizeComponent>(
        background1->getID(), size);

    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        background2->getID(), Type::BACKGROUND);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(
        background2->getID(), std::pair<float, float>(size.first, 0));
    _engine->getComponentManager()->addComponent<component::VelocityComponent>(
        background2->getID(), speed, speed);
    _engine->getComponentManager()->addComponent<component::TextureComponent>(
        background2->getID(), texturePath, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        background2->getID(), size.first, 0, RColor{255, 255, 255, 255}, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::SizeComponent>(
        background2->getID(), size);

    return background1;
}

/**
 * @brief Binds input actions to the specified entity.
 *
 * This function binds various input actions (move left, move right, move up, move down, shoot, and menu)
 * to the corresponding keys (Q, D, Z, S, Space, and Escape) for the given entity.
 *
 * @param entity A pointer to the entity to which the input actions will be bound.
 */
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
    uint32_t entityID = _engine->getEntityManager()->generateEntityID();

    entity::IEntity *player = _engine->getEntityManager()->createEntity(entityID, -1);

    if (_config.contains("player") == false)
    {
        throw rtype::NoPlayerInConfigException("No player configuration found in the JSON file.");
    }

    std::string texturePath = _config["player"]["path"];
    std::pair<float, float> position = std::pair<float, float>(_config["player"]["position"]["x"], _config["player"]["position"]["y"]);
    std::pair<float, float> velocity = std::pair<float, float>(_config["player"]["velocity"]["x"], _config["player"]["velocity"]["y"]);
    std::pair<float, float> scale = std::pair<float, float>(_config["player"]["scale"]["x"], _config["player"]["scale"]["y"]);
    int health = _config["player"]["health"];

    if (_config["player"].contains("weapon"))
    {
        entity::IEntity *weapon = createWeapon(entityID, _config["player"]["weapon"]);
        float speed = _config["player"]["weapon"]["speed"];
        _engine->getComponentManager()->addComponent<component::WeaponComponent>(
            entityID, weapon->getID(), false, speed);
    }

    _engine->getComponentManager()->addComponent<component::TypeComponent>(entityID,
                                                                           Type::PLAYER);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second, getRandomRColor(), _engine->_graphic);
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
entity::IEntity *Game::createEnemy(const nlohmann::json &enemy)
{
    std::string texturePath = enemy["path"];
    int damage = enemy["damage"];
    std::pair<float, float> velocity = std::pair<float, float>(enemy["velocity"]["x"], enemy["velocity"]["y"]);
    std::pair<float, float> scale = std::pair<float, float>(enemy["scale"]["x"], enemy["scale"]["y"]);
    auto positionInput = enemy["position"];
    int health = enemy["health"];
    std::pair<float, float> position;
    std::string iaType = enemy["iaType"];

    if (positionInput["x"] == "random")
        position.first = getRandomPosition();
    else
        position.first = positionInput["x"];
    if (positionInput["y"] == "random")
        position.second = getRandomPosition();
    else
        position.second = positionInput["y"];

    uint32_t entityID = _engine->getEntityManager()->generateEntityID();
    entity::IEntity *enemyEntity = _engine->getEntityManager()->createEntity(entityID, -1);

    if (enemy.contains("weapon") == true)
    {
        auto weaponConfig = enemy["weapon"];
        entity::IEntity *weapon = createWeapon(entityID, weaponConfig);
        float speed = enemy["weapon"]["speed"];
        _engine->getComponentManager()->addComponent<component::WeaponComponent>(
            entityID, weapon->getID(), true, speed);
    }

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

    _engine->getComponentManager()->addComponent<component::TypeComponent>(entityID, Type::ENEMY);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second, RColor{255, 255, 255, 255}, _engine->_graphic);
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

    return enemyEntity;
}

/**
 * @brief Creates a button entity with the specified properties.
 *
 * This function creates a button entity and adds various components to it, such as
 * RectangleShapeComponent, TransformComponent, OnClickComponent, TextComponent, and TypeComponent.
 *
 * @param entityID The unique identifier for the entity.
 * @param color The color of the button.
 * @param position The position of the button in the form of a pair of floats (x, y).
 * @param size The size of the button in the form of a pair of floats (width, height).
 * @param action The action to be performed when the button is clicked.
 * @param numClient The client number associated with the button.
 * @param text The text to be displayed on the button.
 * @param type The type of the entity.
 * @return entity::IEntity* A pointer to the created button entity.
 */
entity::IEntity *Game::createButton(uint32_t entityID, RColor color, std::pair<float, float> position, std::pair<float, float> size, Action action, int numClient, std::string text, Type type)
{
    entity::IEntity *button = _engine->getEntityManager()->createEntity(entityID, numClient);

    _engine->getComponentManager()->addComponent<component::RectangleShapeComponent>(entityID, position, size, color, _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::TransformComponent>(entityID, position, std::pair<float, float>(1, 1));
    _engine->getComponentManager()->addComponent<component::OnClickComponent>(entityID, action, numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(entityID, position, text, 50, RColor{25, 25, 25, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);
    _engine->getComponentManager()->addComponent<component::TypeComponent>(entityID, type);

    return button;
}

/**
 * @brief Creates the menu with various buttons for the game.
 *
 * This function creates several buttons for the game menu, each with a specific action and position.
 * The buttons created are:
 * - Play
 * - Protanopia
 * - Deuteranopia
 * - Tritanopia
 * - Clear Filter
 * - Key Bind
 *
 * Each button is assigned a unique entity ID, color, position, size, action, and label.
 * The scene status for each button is set to MENU.
 *
 * @param numClient The number of clients connected, used to configure the buttons.
 */
void Game::createMenu(int numClient)
{
    entity::IEntity *buttonPlay = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(860.0f, 700.0f), std::pair<float, float>(70.0f, 200.0f), Action::PLAY, numClient, "Play");
    entity::IEntity *buttonProtanopia = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 20.0f), std::pair<float, float>(70.0f, 300.0f), Action::PROTANOPIA, numClient, "Protanopia");
    entity::IEntity *buttonDeuteranopia = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 110.0f), std::pair<float, float>(70.0f, 300.0f), Action::DEUTERANOPIA, numClient, "Deuteranopia");
    entity::IEntity *buttonTritanopia = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 200.0f), std::pair<float, float>(70.0f, 300.0f), Action::TRITANOPIA, numClient, "Tritanopia");
    entity::IEntity *buttonClearFilter = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 290.0f), std::pair<float, float>(70.0f, 300.0f), Action::CLEARFILTER, numClient, "Clear Filter");
    entity::IEntity *buttonKeyBind = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 930.0f), std::pair<float, float>(70.0f, 200.0f), Action::KEYBIND, numClient, "Key Bind");

    buttonPlay->setSceneStatus(Scene::MENU);
    buttonProtanopia->setSceneStatus(Scene::MENU);
    buttonDeuteranopia->setSceneStatus(Scene::MENU);
    buttonTritanopia->setSceneStatus(Scene::MENU);
    buttonClearFilter->setSceneStatus(Scene::MENU);
    buttonKeyBind->setSceneStatus(Scene::MENU);
}

/**
 * @brief Creates key bindings for a client in the game.
 *
 * This function creates several buttons and text components for key bindings
 * and assigns them to a specific client. The buttons and text components are
 * created with specific positions, colors, and actions. The scene status for
 * each button and text component is set to Scene::KEYBIND.
 *
 * @param numClient The client number for which the key bindings are created.
 */
void Game::createKeyBind(int numClient)
{
    entity::IEntity *buttonMoveUp = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 20.0f), std::pair<float, float>(70.0f, 300.0f), Action::MOVE_UP, numClient, "Z", Type::BUTTONBIND);
    entity::IEntity *buttonMoveDown = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 110.0f), std::pair<float, float>(70.0f, 300.0f), Action::MOVE_DOWN, numClient, "S", Type::BUTTONBIND);
    entity::IEntity *buttonMoveLeft = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 200.0f), std::pair<float, float>(70.0f, 300.0f), Action::MOVE_LEFT, numClient, "D", Type::BUTTONBIND);
    entity::IEntity *buttonMoveRight = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 290.0f), std::pair<float, float>(70.0f, 300.0f), Action::KEYMOVERIGHT, numClient, "Q", Type::BUTTONBIND);
    entity::IEntity *buttonShoot = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 380.0f), std::pair<float, float>(70.0f, 300.0f), Action::SHOOT, numClient, "Space", Type::BUTTONBIND);
    entity::IEntity *buttonMenu = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(20.0f, 470.0f), std::pair<float, float>(70.0f, 300.0f), Action::MENU, numClient, "Menu");
    entity::IEntity *buttonPlay = createButton(_engine->getEntityManager()->generateEntityID(), RColor{150, 150, 150, 255}, std::pair<float, float>(860.0f, 700.0f), std::pair<float, float>(70.0f, 200.0f), Action::PLAY, numClient, "Play");

    entity::IEntity *textKeyMoveUp = _engine->getEntityManager()->createEntity(_engine->getEntityManager()->generateEntityID(), numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(textKeyMoveUp->getID(), std::pair<float, float>(320.0f, 20.0f), "Move Up", 50, RColor{255, 255, 255, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);
    entity::IEntity *textKeyMoveDown = _engine->getEntityManager()->createEntity(_engine->getEntityManager()->generateEntityID(), numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(textKeyMoveDown->getID(), std::pair<float, float>(320.0f, 110.0f), "Move Down", 50, RColor{255, 255, 255, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);
    entity::IEntity *textKeyMoveLeft = _engine->getEntityManager()->createEntity(_engine->getEntityManager()->generateEntityID(), numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(textKeyMoveLeft->getID(), std::pair<float, float>(320.0f, 200.0f), "Move Left", 50, RColor{255, 255, 255, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);
    entity::IEntity *textKeyMoveRight = _engine->getEntityManager()->createEntity(_engine->getEntityManager()->generateEntityID(), numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(textKeyMoveRight->getID(), std::pair<float, float>(320.0f, 290.0f), "Move Right", 50, RColor{255, 255, 255, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);
    entity::IEntity *textKeyShoot = _engine->getEntityManager()->createEntity(_engine->getEntityManager()->generateEntityID(), numClient);
    _engine->getComponentManager()->addComponent<component::TextComponent>(textKeyShoot->getID(), std::pair<float, float>(320.0f, 380.0f), "Shoot", 50, RColor{255, 255, 255, 255}, "app/assets/fonts/arial.ttf", _engine->_graphic);

    buttonMoveUp->setSceneStatus(Scene::KEYBIND);
    buttonMoveDown->setSceneStatus(Scene::KEYBIND);
    buttonMoveLeft->setSceneStatus(Scene::KEYBIND);
    buttonMoveRight->setSceneStatus(Scene::KEYBIND);
    buttonShoot->setSceneStatus(Scene::KEYBIND);
    buttonMenu->setSceneStatus(Scene::KEYBIND);
    buttonPlay->setSceneStatus(Scene::KEYBIND);

    textKeyMoveUp->setSceneStatus(Scene::KEYBIND);
    textKeyMoveDown->setSceneStatus(Scene::KEYBIND);
    textKeyMoveLeft->setSceneStatus(Scene::KEYBIND);
    textKeyMoveRight->setSceneStatus(Scene::KEYBIND);
    textKeyShoot->setSceneStatus(Scene::KEYBIND);
}

/**
 * @brief Creates a structure entity based on the provided JSON configuration.
 *
 * This function initializes a new structure entity with various components such as
 * texture, position, scale, health, and others. The entity is created using the
 * entity manager and components are added using the component manager.
 *
 * @param structure A JSON object containing the configuration for the structure.
 * The JSON object should have the following format:
 * {
 *     "path": "path/to/texture",
 *     "position": { "x": float, "y": float },
 *     "scale": { "x": float, "y": float },
 *     "health": int
 * }
 *
 * @return A pointer to the created IEntity representing the structure.
 */
entity::IEntity *Game::createStructure(const nlohmann::json &structure)
{
    std::string texturePath = structure["path"];
    std::pair<float, float> position = std::pair<float, float>(structure["position"]["x"], structure["position"]["y"]);
    std::pair<float, float> scale = std::pair<float, float>(structure["scale"]["x"], structure["scale"]["y"]);
    int health = structure["health"];

    uint32_t entityID = _engine->getEntityManager()->generateEntityID();

    entity::IEntity *structureEntity = _engine->getEntityManager()->createEntity(entityID, -1);

    _engine->getComponentManager()->addComponent<component::TypeComponent>(
        entityID, Type::STRUCTURE);
    _engine->getComponentManager()->addComponent<component::SpriteComponent>(
        entityID, position.first, position.second, RColor{255, 255, 255, 255}, _engine->_graphic);
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

    return structureEntity;
}

/**
 * @brief Reads a JSON configuration file and returns its content as a nlohmann::json object.
 *
 * This function opens the specified file, reads its content, and parses it into a nlohmann::json object.
 * If the file cannot be opened, it throws a std::runtime_error.
 *
 * @param path The path to the JSON configuration file.
 * @return A nlohmann::json object containing the parsed content of the file.
 * @throws std::runtime_error If the file cannot be opened.
 */
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
 *
 * - Player with ID 0, sprite located at "app/assets/sprites/r-typesheet1.gif",
 *   initial position (100.0f, 100.0f), velocity (10.0f, 0.0f), and scale
 * (1.0f, 1.0f).
 *
 * - Background with ID 1, image located at
 * "app/assets/images/city_background.png", initial position (100.0f, 0.0f), and
 * size (1920.0f, 1080.0f).
 *
 * The following systems are added to the system manager:
 * - Audio system
 *
 * - Render system
 *
 * - Input system
 *
 * - Movement system
 *
 * - Background system
 *
 * The following input actions are bound to keys for the player with ID 0:
 * - "MoveLeft" to the 'A' key
 *
 * - "MoveRight" to the 'D' key
 *
 * - "MoveUp" to the 'W' key
 *
 * - "MoveDown" to the 'S' key
 *
 */
void Game::init()
{
    ECS_system::StringCom stringCom;
    stringCom.texturePath[TexturePath::Player] = "app/assets/sprites/plane.png";
    stringCom.texturePath[TexturePath::Enemy] = "app/assets/sprites/enemy.png";
    stringCom.texturePath[TexturePath::Background] = "app/assets/images/background.jpg";
    stringCom.texturePath[TexturePath::Bullet] = "app/assets/sprites/projectile.gif";
    stringCom.texturePath[TexturePath::Structure] = "app/assets/sprites/block.png";
    stringCom.textFont[TextFont::Arial] = "app/assets/fonts/arial.ttf";
    stringCom.textString[TextString::Play] = "Play";
    stringCom.textString[TextString::Protanopia] = "Protanopia";
    stringCom.textString[TextString::Deuteranopia] = "Deuteranopia";
    stringCom.textString[TextString::Tritanopia] = "Tritanopia";
    stringCom.textString[TextString::ClearFilter] = "Clear Filter";
    stringCom.textString[TextString::KeyBind] = "Key Bind";
    stringCom.textString[TextString::Menu] = "Menu";
    stringCom.textString[TextString::MoveUp] = "Move Up";
    stringCom.textString[TextString::MoveDown] = "Move Down";
    stringCom.textString[TextString::MoveLeft] = "Move Left";
    stringCom.textString[TextString::MoveRight] = "Move Right";
    stringCom.textString[TextString::Shoot] = "Shoot";
    stringCom.textString[TextString::Z] = "Z";
    stringCom.textString[TextString::S] = "S";
    stringCom.textString[TextString::Q] = "Q";
    stringCom.textString[TextString::D] = "D";
    stringCom.textString[TextString::Space] = "Space";
    stringCom.textString[TextString::PressKey] = "Press a key";
    stringCom.soundPath[SoundPath::Shoot] = "app/assets/musics/blaster.wav";
    stringCom.soundPath[SoundPath::BackgroundMusic] = "app/assets/musics/dancin.ogg";

    try
    {
        this->setConfig(this->fillConfigJson("configs/config1.json"));

        this->createBackground();

        if (_config.contains("waveSystem"))
        {
            int waveInterval = _config["waveSystem"]["waveInterval"];
            int waveNumber = _config["waveSystem"]["waveNumber"];
            this->_waveInterval = waveInterval;
            this->_waveNumber = waveNumber;
        }

        if (_config.contains("structure") && _config["structure"].is_array())
        {
            for (const auto &structure : _config["structure"])
            {
                _spawnClocks.push_back({false, rtype::Clock()});
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    component::ComponentManager &componentManager = *_engine->getComponentManager();

    entity::EntityManager &entityManager = *_engine->getEntityManager();

    if (_config.contains("serverSystems") == true)
    {
        if (!_config["serverSystems"].is_array())
            throw rtype::InvalidSystemConfigException("Invalid system configuration in JSON file.");
        else
        {
            for (const auto &system : _config["serverSystems"])
                _engine->getSystemManager()->addSystem(componentManager, entityManager, system, _engine->_graphic, _engine->_audio, stringCom);
        }
    }
}

/**
 * @brief Adds a filter entity to the game based on the specified filter type.
 *
 * This function creates a new filter entity and adds the appropriate components
 * to it based on the specified filter type. The filter types supported are
 * "protanopia", "deuteranopia", and "tritanopia". Each filter type corresponds
 * to a different color overlay.
 *
 * @param filter The type of filter to add. Supported values are "protanopia",
 * "deuteranopia", and "tritanopia".
 * @param numClient The client number associated with the filter entity.
 * @return entity::IEntity* A pointer to the created filter entity.
 */
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
    return filterEntity;
}

/**
 * @brief Handles received messages and performs corresponding actions.
 *
 * This function processes a list of received messages and executes the appropriate
 * actions based on the message type. The messages are expected to be in the form of
 * a vector of pairs, where each pair contains a string message and another pair
 * consisting of a size_t ID and an int client number.
 *
 * @param msgReceived A reference to a vector of pairs containing the received messages.
 *
 * The function supports the following message types:
 * - "clientConnection": Handles client connection, sets up the menu, and creates key bindings.
 * - "clientDisconnection": Handles client disconnection, deletes the player's entity if it exists.
 * - "play": Starts the game, initializes player entities, and sets the scene to GAME.
 * - "keyBind": Sets the scene to KEYBIND and sends a key binding action.
 * - "protanopia": Applies the protanopia filter to the player's view.
 * - "deuteranopia": Applies the deuteranopia filter to the player's view.
 * - "tritanopia": Applies the tritanopia filter to the player's view.
 * - "clearFilter": Clears any color filter applied to the player's view.
 * - "menu": Sets the scene to MENU and sends a menu action.
 * - "moveUp", "moveDown", "moveLeft", "moveRight": Moves the player's entity in the specified direction.
 * - "shoot": Makes the player's entity shoot.
 *
 * The function also ensures that actions are only performed if the player exists and the
 * player ID matches the provided ID.
 */
void Game::handleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived)
{
    std::string msg = msgReceived.front().first;
    size_t id = msgReceived.front().second.first;
    int numClient = msgReceived.front().second.second;
    msgReceived.erase(msgReceived.begin());
    if (msg == "clientConnection")
    {

        _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::MENU, numClient));
        _playersScenes[numClient] = Scene::MENU;
        createKeyBind(numClient);
        createMenu(numClient);
    }
    if (msg == "clientDisconnection")
    {
        if (_players.find(numClient) != _players.end())
        {
            entity::IEntity *entity = _engine->getEntityManager()->getEntityByID(_players[numClient]);
            if (entity)
                entity->setCommunication(entity::EntityCommunication::DELETE);
            _players.erase(numClient);
        }
    }
    if (msg == "play")
    {
        for (auto &spawnClocks : _spawnClocks)
            spawnClocks.second.restart();
        _isStarted = true;
        _waveClock.restart();
        if (_playersScenes[numClient] == Scene::GAME)
            return;
        if (_players.find(numClient) == _players.end())
        {
            entity::IEntity *entity = createPlayer(numClient);
            _players[numClient] = entity->getID();
        }
        _playersScenes[numClient] = Scene::GAME;
        _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::GAME, numClient));
    }
    if (msg == "keyBind")
    {
        if (_playersScenes[numClient] == Scene::KEYBIND)
            return;
        _playersScenes[numClient] = Scene::KEYBIND;
        _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::KEYBIND, numClient));
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
    if (_players.find(numClient) == _players.end())
        return;
    if (_players[numClient] != id)
        return;
    if (msg == "moveUp" || msg == "moveDown" || msg == "moveLeft" || msg == "moveRight")
        moveEntity(msg, id);
    if (msg == "shoot")
        shootEntity(id);
}

/**
 * @brief Triggers the firing mechanism of an entity's weapon.
 *
 * This function sets the `isFiring` flag to true for the weapon component
 * associated with the specified entity ID, if the entity has a weapon component.
 *
 * @param id The unique identifier of the entity whose weapon should be fired.
 */
void Game::shootEntity(size_t id)
{
    if (_engine->getComponentManager()->getComponent<component::WeaponComponent>(id))
    {
        component::WeaponComponent *weaponComponent = _engine->getComponentManager()->getComponent<component::WeaponComponent>(id);
        weaponComponent->setIsFiring(true);
    }
}

/**
 * @brief Moves an entity based on the provided message.
 *
 * This function updates the velocity of an entity identified by its ID
 * according to the specified movement command. The entity's velocity
 * components are adjusted to reflect the desired movement direction.
 *
 * @param msg The movement command, which can be one of the following:
 *            - "moveUp": Moves the entity upwards.
 *            - "moveDown": Moves the entity downwards.
 *            - "moveLeft": Moves the entity to the left.
 *            - "moveRight": Moves the entity to the right.
 * @param id The unique identifier of the entity to be moved.
 */
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

/**
 * @brief Resets the input for all entities that have both InputComponent and VelocityComponent.
 *
 * This function iterates through all entities managed by the engine's entity manager. For each entity,
 * it checks if the entity has both an InputComponent and a VelocityComponent. If both components are present,
 * and the entity's velocity is non-zero, and the elapsed time since the last input reset is greater than 0.1 seconds,
 * the function sets the entity's velocity to zero, updates the component communication status, and restarts the input clock.
 */
void Game::resetInput()
{
    std::vector<std::shared_ptr<entity::IEntity>> entities = _engine->getEntityManager()->getEntities();

    for (auto &entity : entities)
    {
        if (_engine->getComponentManager()->getComponent<component::InputComponent>(entity->getID()))
        {
            if (_engine->getComponentManager()->getComponent<component::VelocityComponent>(entity->getID()))
            {
                component::VelocityComponent *velocityComponent = _engine->getComponentManager()->getComponent<component::VelocityComponent>(entity->getID());
                if ((velocityComponent->getActualVelocity().first != 0 || velocityComponent->getActualVelocity().second != 0) && _inputClock.getElapsedTime() > 0.1)
                {
                    velocityComponent->setActualVelocityX(0);
                    velocityComponent->setActualVelocityY(0);
                    velocityComponent->setCommunication(component::ComponentCommunication::UPDATE);
                    _inputClock.restart();
                }
            }
        }
    }
}

/**
 * @brief Main game loop that runs the game logic.
 *
 * This function initializes the random seed, restarts the input clock, and enters the main game loop.
 * The loop continues running while the game is marked as running (_isRunning).
 *
 * Inside the loop:
 * - The game engine is updated.
 *
 * - Players are checked for their corresponding entities, and if an entity is not found, the player is removed and a message is sent.
 *
 * - Waves of enemies are spawned based on the configuration and wave interval.
 *
 * - Structures are created based on the configuration and spawn timers.
 *
 * - If all waves are completed and there are still players, a win message is displayed and the game is marked as not started.
 *
 * - Received messages are handled, and if no messages are received, the input is reset.
 *
 * @throws rtype::NoPlayerInConfigException if there is an issue with player configuration.
 */
void Game::run()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    _inputClock.restart();
    while (_isRunning)
    {
        _engine->update();
        for (auto it = _players.begin(); it != _players.end();)
        {
            entity::IEntity *entity = _engine->getEntityManager()->getEntityByID(it->second);
            if (!entity)
            {
                _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::MENU, it->first));
                it = _players.erase(it);
            }
            else
            {
                ++it;
            }
        }
        if (_waveNumber != 0 && _waveClock.getElapsedTime() > _waveInterval && _isStarted)
        {
            if (_config.contains("enemy") && _config["enemy"].is_array())
            {
                for (const auto &enemy : _config["enemy"])
                    this->createEnemy(enemy);
            }
            else
                std::cerr << "Warning: 'enemy' not found or is not an array in config." << std::endl;

            _waveNumber--;
            _waveClock.restart();
        }

        if (!_structureCreated && _isStarted)
        {
            if (_config.contains("structure") && _config["structure"].is_array())
            {
                if (_spawnClocks.size() >= _config["structure"].size())
                {
                    for (size_t i = 0; i < _config["structure"].size(); ++i)
                    {
                        if (!_spawnClocks[i].first)
                        {
                            const auto &structure = _config["structure"][i];

                            float timer = structure["timer"];
                            if (_spawnClocks[i].second.getElapsedTime() > timer)
                            {
                                this->createStructure(structure);
                                _createdStructure++;
                                _spawnClocks[i].first = true;
                                _spawnClocks[i].second.restart();
                            }
                        }
                    }
                }
                else
                    std::cerr << "Erreur : _spawnClocks n'a pas assez d'éléments pour correspondre à config[\"structure\"]." << std::endl;
                if (_createdStructure == _config["structure"].size())
                    _structureCreated = true;
            }
            else
                std::cerr << "Warning: 'structure' not found or is not an array in config." << std::endl;
        }

        if (_players.size() != 0 && _waveNumber == 0 && _isStarted)
        {
            _isStarted = false;
            _waveNumber = _config["waveSystem"]["waveNumber"];
            _structureCreated = false;
            _createdStructure = 0;
            for (auto &spawnClocks : _spawnClocks)
            {
                spawnClocks.first = false;
                spawnClocks.second.restart();
            }
            for (auto &player : _players)
            {
                _playersScenes[player.first] = Scene::MENU;
                _engine->msgToSend.push_back(std::pair<Action, size_t>(Action::MENU, player.first));
            }
        }

        if (!_engine->msgReceived.empty())
        {
            try
            {
                handleReceivedMessage(_engine->msgReceived);
            }
            catch (const rtype::NoPlayerInConfigException &e)
            {
                std::cerr << e.what() << '\n';
                // disconnect the client
            }
        }
        else
        {
            resetInput();
        }
    }
}