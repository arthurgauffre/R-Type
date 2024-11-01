/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ButtonSystem
*/

#pragma once

#include <components/RectangleShapeComponent.hpp>
#include <components/OnClickComponent.hpp>
#include <components/TransformComponent.hpp>
#include <managers/ComponentManager.hpp>
#include <managers/EntityManager.hpp>

#include <r-type/ASystem.hpp>

namespace ECS_system
{
    class ButtonSystem : virtual public ASystem
    {
    public:
        ButtonSystem(component::ComponentManager &componentManager,
                     entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, StringCom stringCom);
        ~ButtonSystem() = default;

        void
        update(float deltaTime,
               std::vector<std::shared_ptr<entity::IEntity>> entities,
               std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

        /**
         * @brief Initializes the collision system.
         *
         * This method is called to set up any necessary resources or configurations
         * for the collision system. It overrides the base class implementation.
         */
        void initialize() override {};

        /**
         * @brief Handles the collision components within the ECS framework.
         *
         * This function is an override of the base class method and is responsible
         * for managing and updating the collision components in the system. The
         * actual implementation details should be provided in the function body.
         */
        void handleComponents() override {};
    };
} // namespace ECS_system