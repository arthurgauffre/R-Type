/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include <RtypeEngine.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <cmath>
#include <random>

class Game
{
public:
    Game(std::shared_ptr<rtype::RtypeEngine> engine);
    ~Game();

    entity::IEntity *createBackground();
    entity::IEntity *createPlayer(int numClient);
    entity::IEntity *createEnemy(const nlohmann::json &enemy);
    entity::IEntity *createWeapon(uint32_t parentID, Type type, int damage,
                                  float cooldown);
    entity::IEntity *createButton(uint32_t entityID, RColor color, std::pair<float, float> position, std::pair<float, float> size, Action action, int numClient, std::string text = "Play");

    void createMenu(int numClient);

    entity::IEntity *createStructure();

    void init();
    void run();
    void resetInput();
    void moveEntity(std::string msg, size_t id);
    void shootEntity(size_t id);
    void handdleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived);

    entity::IEntity *addFilter(std::string filter, int numClient);

    nlohmann::json fillConfigJson(const std::string &path);
    void BindInputScript(entity::IEntity *entity);

    void setConfig(nlohmann::json config) { _config = config; }
    nlohmann::json getConfig() { return _config; }

protected:
private:
    int _waveNumber;
    std::shared_ptr<rtype::RtypeEngine> _engine;
    sf::Clock _inputClock;
    sf::Clock _waveClock;
    sf::Clock _spawnClock;
    std::unordered_map<size_t, entity::IEntity *> _players;
    std::unordered_map<size_t, Scene> _playersScenes;
    std::unordered_map<int, std::pair<entity::IEntity *, std::string>> _playersFilters;
    float _spawnInterval;
    float _waveInterval;
    nlohmann::json _config;
    bool _isStarted;
};
