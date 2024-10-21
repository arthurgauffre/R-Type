/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientReceiveSystem
*/

#include <systems/ClientReceiveSystem.hpp>

namespace ECS_system {
    std::vector<std::string> ClientReceiveSystem::update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::string> msgToSend) {
        return msgToSend;
    }
}