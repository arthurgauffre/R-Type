/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AISytem
*/

#pragma once

#include <r-type/ASystem.hpp>

#include <components/AIComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/VelocityComponent.hpp>
#include <components/TransformComponent.hpp>

#include <cmath>

namespace ECS_system
{
    class AISytem : virtual public ASystem
    {
    public:
        AISytem(component::ComponentManager &componentManager,
                entity::EntityManager &entityManager)
            : ASystem(componentManager, entityManager) {}
        ~AISytem() = default;

        void update(float deltaTime,
                    std::vector<std::shared_ptr<entity::IEntity>> entities,
                    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived, std::mutex &entityMutex) override;

        void initialize() override {};
        void handleComponents() override {};

    private:
    };
}