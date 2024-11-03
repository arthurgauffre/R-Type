/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include <RtypeEngine.hpp>
#include <Error.hpp>
#include <Clock.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <cmath>
#include <random>

class Game
{
public:
    /**
     * @brief Constructs a new Game object.
     *
     * @param engine A shared pointer to an RtypeEngine instance.
     */
    Game(std::shared_ptr<rtype::RtypeEngine> engine);

    /**
     * @brief Destructor for the Game class.
     *
     * This destructor is responsible for cleaning up resources
     * and performing any necessary finalization when a Game object
     * is destroyed.
     */
    ~Game();

    /**
     * @brief Creates a background entity.
     *
     * This function is responsible for creating and returning a pointer to a background entity.
     *
     * @return A pointer to an IEntity representing the background.
     */
    entity::IEntity *createBackground();

    /**
     * @brief Creates a player entity for the specified client.
     *
     * @param numClient The client number for which the player entity is to be created.
     * @return A pointer to the created player entity.
     */
    entity::IEntity *createPlayer(int numClient);
    entity::IEntity *createEnemy(const nlohmann::json &enemy);
    entity::IEntity *createWeapon(uint32_t parentID, nlohmann::json &weapon);

    /**
     * @brief Creates a button entity.
     *
     * @param entityID The unique identifier for the entity.
     * @param color The color of the button.
     * @param position The position of the button as a pair of floats (x, y).
     * @param size The size of the button as a pair of floats (width, height).
     * @param action The action to be performed when the button is pressed.
     * @param numClient The client number associated with the button.
     * @param text The text displayed on the button. Default is "Play".
     * @return A pointer to the created button entity.
     */
    entity::IEntity *createButton(uint32_t entityID, RColor color, std::pair<float, float> position, std::pair<float, float> size, Action action, int numClient, std::string text = "Play", Type type = Type::BUTTON);

    /**
     * @brief Creates a menu for the game.
     *
     * This function is responsible for creating a menu interface for the game
     * based on the number of clients connected.
     *
     * @param numClient The number of clients connected to the game.
     */
    void createMenu(int numClient);

    /**
     * @brief Creates a key binding for a client.
     * 
     * This function sets up the key bindings for a specific client identified by the given client number.
     * 
     * @param numClient The identifier for the client for whom the key bindings are being created.
     */
    void createKeyBind(int numClient);

    /**
     * @brief Creates a structure entity with the specified parameters.
     *
     * @param entityID The unique identifier for the entity.
     * @param texturePath The file path to the texture to be used for the entity.
     * @param position A pair representing the x and y coordinates of the entity's position.
     * @param scale A pair representing the x and y scaling factors of the entity.
     * @param health The health value of the entity.
     * @return A pointer to the created IEntity object.
     */
    entity::IEntity *createStructure(const nlohmann::json &structure);

    /**
     * @brief Initializes the game.
     *
     * This function sets up the necessary components and state for the game to start.
     */
    void init();

    /**
     * @brief Starts the game loop and manages the game state.
     *
     * This function initiates the main game loop, handling all game logic,
     * updates, and rendering. It continues running until the game is
     * terminated or an exit condition is met.
     */
    void run();

    /**
     * @brief Resets the input state to its default values.
     *
     * This function is used to clear or reset any input-related data or states
     * within the game. It ensures that the input system is in a known state,
     * typically at the beginning of a new game or level.
     */
    void resetInput();

    /**
     * @brief Moves an entity based on the provided message and entity ID.
     *
     * This function processes the given message to determine the movement
     * instructions for the entity identified by the specified ID. The exact
     * format and content of the message should be defined elsewhere in the
     * documentation.
     *
     * @param msg A string containing the movement instructions for the entity.
     * @param id The unique identifier of the entity to be moved.
     */
    void moveEntity(std::string msg, size_t id);

    /**
     * @brief Shoots an entity with the given ID.
     *
     * This function triggers the shooting mechanism for the entity identified by the specified ID.
     *
     * @param id The unique identifier of the entity to shoot.
     */
    void shootEntity(size_t id);

    /**
     * @brief Handles the received messages.
     *
     * This function processes a vector of received messages, where each message is represented as a pair.
     * The first element of the pair is a string containing the message content, and the second element is a pair of size_t values.
     *
     * @param msgReceived A reference to a vector of pairs, where each pair consists of a string and a pair of size_t values.
     */
    void handleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived);

    /**
     * @brief Adds a filter to the game.
     *
     * This function adds a filter to the game based on the provided filter string
     * and the number of clients. It returns a pointer to the newly created entity
     * that represents the filter.
     *
     * @param filter The filter string to be added.
     * @param numClient The number of clients associated with the filter.
     * @return entity::IEntity* Pointer to the newly created entity representing the filter.
     */
    entity::IEntity *addFilter(std::string filter, int numClient);

    /**
     * @brief Fills a JSON object with configuration data from a file.
     *
     * This function reads a configuration file from the specified path and
     * populates a JSON object with the data contained in the file.
     *
     * @param path The path to the configuration file.
     * @return nlohmann::json The JSON object containing the configuration data.
     */
    nlohmann::json fillConfigJson(const std::string &path);

    /**
     * @brief Binds an input script to the specified entity.
     *
     * This function associates an input handling script with the given entity,
     * allowing the entity to respond to user inputs.
     *
     * @param entity A pointer to the IEntity object to which the input script will be bound.
     */
    void BindInputScript(entity::IEntity *entity);

    /**
     * @brief Sets the configuration for the game.
     *
     * @param config A JSON object containing the configuration settings.
     */
    void setConfig(nlohmann::json config) { _config = config; }
protected:
private:
    /**
     * @brief The current wave number in the game.
     */
    int _waveNumber;

    /**
     * @brief A shared pointer to an instance of the RtypeEngine.
     *
     * This shared pointer manages the lifetime of the RtypeEngine instance,
     * ensuring that the engine is properly destroyed when no longer in use.
     * It allows multiple parts of the program to share ownership of the
     * RtypeEngine instance.
     */
    std::shared_ptr<rtype::RtypeEngine> _engine;
    rtype::Clock _inputClock;
    rtype::Clock _waveClock;
    std::vector<std::pair<bool, rtype::Clock>> _spawnClocks;
    std::unordered_map<size_t, size_t> _players;

    /**
     * @brief A map that associates player IDs with their corresponding scenes.
     *
     * This unordered map uses player IDs (of type size_t) as keys and Scene objects as values.
     * It allows for efficient retrieval and management of scenes for each player.
     */
    std::unordered_map<size_t, Scene> _playersScenes;

    /**
     * @brief A map that associates player IDs with their corresponding entity and filter string.
     *
     * The key is an integer representing the player ID.
     * The value is a pair consisting of:
     * - A pointer to an IEntity object representing the player's entity.
     * - A string representing the player's filter.
     */
    std::unordered_map<int, std::pair<entity::IEntity *, std::string>> _playersFilters;
    float _waveInterval;

    /**
     * @brief Configuration data in JSON format.
     *
     * This member variable holds the configuration settings for the game,
     * stored in a JSON object using the nlohmann::json library.
     */
    nlohmann::json _config;
    bool _isStarted;
    bool _isRunning;
    bool _structureCreated;
    int _createdStructure;
};
