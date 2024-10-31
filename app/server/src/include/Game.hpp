/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include <CoreModule.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

#include <random>

class Game
{
public:
    Game(std::shared_ptr<rtype::CoreModule> coreModule);
    ~Game();

    entity::IEntity *createBackground();
    entity::IEntity *createPlayer(int numClient);
    entity::IEntity *createEnemy();
    entity::IEntity *createWeapon(uint32_t parentID, component::Type type, int damage,
                                  float cooldown);

    entity::IEntity *createStructure(uint32_t entityID, std::string texturePath,
                                     std::pair<float, float> position,
                                     std::pair<float, float> scale, int health);

    void init();
    void run();
    void resetInput();
    void moveEntity(std::string msg, size_t id);
    void shootEntity(size_t id);
    void handdleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived);

    nlohmann::json fillConfigJson(const std::string &path);

    void setConfig(nlohmann::json config) { _config = config; }
    nlohmann::json getConfig() { return _config; }

protected:
private:
    int _waveNumber;
    std::shared_ptr<rtype::CoreModule> _coreModule;
    sf::Clock inputClock;
    sf::Clock waveClock;
    std::unordered_map<size_t, entity::IEntity *> _players;
    float _waveInterval;
    nlohmann::json _config;
};
