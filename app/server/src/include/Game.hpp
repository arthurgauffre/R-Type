/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include <CoreModule.hpp>

class Game
{
public:
    Game(std::shared_ptr<rtype::CoreModule> coreModule);
    ~Game();

    // entity::IEntity *createBackground(uint32_t entityID, std::string texturePath,
    //                                   std::pair<float, float> speed,
    //                                   std::pair<float, float> size);
    entity::IEntity *createPlayer(uint32_t entityID, std::string texturePath,
                                  std::pair<float, float> position,
                                  std::pair<float, float> velocity,
                                  std::pair<float, float> scale, int health);
    // entity::IEntity *createEnemy(uint32_t entityID, std::string texturePath,
    //                              std::pair<float, float> position,
    //                              std::pair<float, float> velocity,
    //                              std::pair<float, float> scale, int health,
    //                              int damage);
    // entity::IEntity *createWeapon(uint32_t parentID, std::string type, int damage,
    //                               float cooldown);

    void init();
    void run();
    void handdleReceivedMessage(std::vector<std::pair<std::string, size_t>> &msgReceived);

protected:
private:
    std::shared_ptr<rtype::CoreModule> _coreModule;
};
