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
                entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, StringCom stringCom)
            : ASystem(componentManager, entityManager, graphic, stringCom) {}
        ~AISytem() = default;

        void update(float deltaTime,
                    std::vector<std::shared_ptr<entity::IEntity>> entities,
                    std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

        void initialize() override {};
        void handleComponents() override {};

    private:
    };
}