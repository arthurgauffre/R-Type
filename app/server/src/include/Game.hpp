/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include <RtypeEngine.hpp>

#include <random>

class Game
{
public:
    Game(std::shared_ptr<rtype::RtypeEngine> coreModule);
    ~Game();

    entity::IEntity *createBackground(std::string texturePath,
                                      std::pair<float, float> speed,
                                      std::pair<float, float> size);
    entity::IEntity *createPlayer(uint32_t entityID, std::string texturePath,
                                  std::pair<float, float> position,
                                  std::pair<float, float> velocity,
                                  std::pair<float, float> scale, int health, int numClient);
    entity::IEntity *createEnemy(uint32_t entityID, std::string texturePath,
                                 std::pair<float, float> position,
                                 std::pair<float, float> velocity,
                                 std::pair<float, float> scale, int health,
                                 int damage);
    entity::IEntity *createWeapon(uint32_t parentID, component::Type type, int damage,
                                  float cooldown);

    void init();
    void run();
    void resetInput();
    void moveEntity(std::string msg, size_t id);
    void shootEntity(size_t id);
    void handdleReceivedMessage(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived);

protected:
private:
    int _waveNumber;
    std::shared_ptr<rtype::RtypeEngine> _coreModule;
    sf::Clock inputClock;
    sf::Clock waveClock;
    std::unordered_map<size_t, entity::IEntity *> _players;
    float _spawnInterval;
};
