/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AudioSystem
*/

#pragma once

#include "ASystem.hpp"
#include "SoundComponent.hpp"
#include "MusicComponent.hpp"

namespace ECS_system
{
    class AudioSystem : public ASystem
    {
    public:
        AudioSystem(component::ComponentManager &componentManager) : ASystem(componentManager) {}
        ~AudioSystem() = default;

        void update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) override;
        void initialize() override {};
        void handleComponents() override {};

    private:
    };
}