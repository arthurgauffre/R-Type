/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AIComponent
*/

#include <components/AIComponent.hpp>

namespace component
{
    /**
     * @brief Constructs an AIComponent object.
     *
     * @param entityID The unique identifier for the entity associated with this component.
     * @param type The type of AI associated with this component.
     */
    AIComponent::AIComponent(uint32_t entityID, AIType type) : AComponent(entityID), _type(type) {}

    /**
     * @brief Destructor for the AIComponent class.
     *
     * This destructor is responsible for cleaning up any resources
     * or memory allocated by the AIComponent instance. It ensures
     * that when an AIComponent object is destroyed, all associated
     * resources are properly released.
     */
    AIComponent::~AIComponent() {}

    /**
     * @brief Retrieves the type of the AI component.
     *
     * @return AIType The type of the AI component.
     */
    AIType AIComponent::getType() { return this->_type; }

    /**
     * @brief Sets the type of the AI component.
     *
     * @param type The AIType to set for this component.
     */
    void AIComponent::setType(AIType type) { this->_type = type; }

    /**
     * @brief Retrieves the elapsed time for the AI component.
     *
     * @return float The elapsed time for the AI component.
     */
    float AIComponent::getElapsedTime() { return this->_elapsedTime; }

    /**
     * @brief Sets the elapsed time for the AI component.
     *
     * @param elapsedTime The elapsed time to set for the AI component.
     */
    void AIComponent::setElapsedTime(float elapsedTime) { this->_elapsedTime = elapsedTime; }

    /**
     * @brief Updates the AI component.
     *
     * This function updates the AI component based on the type of AI
     * and the elapsed time.
     *
     * @param type The type of AI to update.
     * @param elapsedTime The elapsed time to update.
     */
    void AIComponent::update(AIType type, float elapsedTime)
    {
        this->_type = type;
        this->_elapsedTime = elapsedTime;
    }
}