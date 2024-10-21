/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ServerReceiveSystem
*/

#include <systems/ServerReceiveSystem.hpp>

namespace ECS_system {
std::vector<std::string> ServerReceiveSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::string> msgToSend) {
  return msgToSend;
}
} // namespace ECS_system