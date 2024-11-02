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
#include <components/TypeComponent.hpp>
#include <components/InputComponent.hpp>
#include <components/TextComponent.hpp>
#include <managers/ComponentManager.hpp>
#include <managers/EntityManager.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

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
         * @brief Changes the input state of the given entities based on the keyboard key and action.
         * 
         * @param entities A vector of shared pointers to IEntity objects representing the entities whose input state will be changed.
         * @param key The KeyBoard key that was pressed or released.
         * @param action The action associated with the key press or release.
         */
        void changeInput(std::vector<std::shared_ptr<entity::IEntity>> entities, KeyBoard key, Action action);

        /**
         * @brief Binds a keyboard key to a specific action.
         * 
         * This function associates a given keyboard key with a specified action,
         * allowing the key to trigger the action when pressed.
         * 
         * @param key The keyboard key to bind.
         * @param action The action to be triggered by the key.
         */
        void bindTheKey(KeyBoard key, Action action);

        /**
         * @brief Changes the text of the given entity based on the keyboard input.
         * 
         * @param entity A pointer to the entity whose text will be changed.
         * @param key The keyboard input that determines the new text.
         */
        void changeText(size_t id, KeyBoard key, std::shared_ptr<IGraphic> graphic);

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