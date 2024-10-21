/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientSendSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

namespace ECS_system {
    class ClientSendSystem: virtual public ASystem {
        public:
            ClientSendSystem(component::ComponentManager &componentManager, entity::EntityManager &entityManager)
                : ASystem(componentManager, entityManager) {}
            ~ClientSendSystem() = default;

            std::vector<std::string> update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::string> msgToSend) override;
            void initialize() override{};
            void handleComponents() override{};
    };
}