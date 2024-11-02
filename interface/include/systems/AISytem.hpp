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
        /**
         * @brief Constructs an AISytem object.
         *
         * @param componentManager Reference to the ComponentManager instance.
         * @param entityManager Reference to the EntityManager instance.
         * @param graphic Shared pointer to an IGraphic instance.
         * @param stringCom StringCom object.
         */
        AISytem(component::ComponentManager &componentManager,
                entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, StringCom stringCom)
            : ASystem(componentManager, entityManager, graphic, stringCom) {}

        /**
         * @brief Default destructor for the AISystem class.
         *
         * This destructor is used to clean up resources when an instance of the AISystem class is destroyed.
         */
        ~AISytem() = default;

        /**
         * @brief Updates the AI system.
         *
         * @param deltaTime The time elapsed since the last update.
         * @param entities A vector of shared pointers to entities that the AI system will process.
         * @param msgToSend A reference to a vector of pairs containing actions and entity IDs to send messages.
         * @param msgReceived A reference to a vector of pairs containing message strings and their associated entity IDs.
         * @param entityMutex A reference to a mutex for synchronizing access to entities.
         * @param sceneStatus A shared pointer to the current scene status.
         */
        void update(float deltaTime,
                    std::vector<std::shared_ptr<entity::IEntity>> entities,
                    std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

        /**
         * @brief Initializes the AI system.
         *
         * This function is called to set up any necessary state or resources
         * for the AI system before it starts processing.
         */
        void initialize() override {};

        /**
         * @brief Handles the components associated with the AI system.
         *
         * This function overrides the base class implementation to provide
         * specific handling for AI-related components within the system.
         */
        void handleComponents() override {};

    private:
    };
}