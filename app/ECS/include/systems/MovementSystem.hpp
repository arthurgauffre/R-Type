/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem
*/

#pragma once

#include "ASystem.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "PositionComponent.hpp"

#include <SFML/System/Time.hpp>

namespace ECS_system
{
    class MovementSystem : public ASystem
    {
    public:
        /**
         * @class MovementSystem
         * @brief A system responsible for handling the movement of entities.
         *
         * This class inherits from ASystem and is used to manage and update the
         * movement-related components of entities within the ECS framework.
         *
         * @param componentManager A reference to the ComponentManager that manages
         *                         all components in the ECS.
         */
        MovementSystem(component::ComponentManager &componentManager)
            : ASystem(componentManager) {}

        /**
         * @brief Default destructor for the MovementSystem class.
         *
         */
        ~MovementSystem() = default;

        /**
         * @brief Initializes the MovementSystem.
         *
         * This function initializes the MovementSystem by setting up any required
         * resources or state.
         */
        void initialize() override {};

        /**
         * @brief Updates the MovementSystem.
         *
         * This function updates the MovementSystem based on the elapsed time and the
         * entities provided.
         *
         * @param deltaTime The time elapsed since the last update, in seconds.
         * @param entities A vector of shared pointers to the entities to be updated.
         */
        void update(float deltaTime,
                    std::vector<std::shared_ptr<entity::IEntity>> entities) override;

        /**
         * @brief Handles the components of the MovementSystem.
         *
         * This function handles the components of the MovementSystem by updating the
         * position of entities based on their velocity.
         */
        void handleComponents() override {};

    protected:
    private:
    };
}