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
        /**
         * @brief Constructs a new ButtonSystem object.
         *
         * @param componentManager Reference to the ComponentManager instance.
         * @param entityManager Reference to the EntityManager instance.
         * @param graphic Shared pointer to an IGraphic instance.
         * @param stringCom StringCom object.
         */
        ButtonSystem(component::ComponentManager &componentManager,
                     entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, StringCom stringCom);

        /**
         * @brief Default destructor for the ButtonSystem class.
         */
        ~ButtonSystem() = default;

        /**
         * @brief Updates the state of the button system.
         *
         * @param deltaTime The time elapsed since the last update.
         * @param entities A vector of shared pointers to the entities to be updated.
         * @param msgToSend A reference to a vector of pairs containing actions and their corresponding entity IDs to be sent.
         * @param msgReceived A reference to a vector of pairs containing messages and their corresponding sender and receiver IDs.
         * @param entityMutex A reference to a mutex for synchronizing access to entities.
         * @param sceneStatus A shared pointer to the current scene status.
         */
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