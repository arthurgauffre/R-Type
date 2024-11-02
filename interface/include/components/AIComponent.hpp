/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AIComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component
{
  class AIComponent : public AComponent
  {
  public:
    /**
     * @brief Constructs an AIComponent with the specified entity ID and AI type.
     *
     * @param entityID The unique identifier of the entity this component is associated with.
     * @param type The type of AI behavior this component will exhibit.
     */
    AIComponent(uint32_t entityID, AIType type);

    /**
     * @brief Destructor for the AIComponent class.
     *
     * This destructor is responsible for cleaning up any resources
     * that the AIComponent may have acquired during its lifetime.
     */
    ~AIComponent();

    AIType getType();
    /**
     * @brief Sets the type of the AI component.
     *
     * @param type The AIType to set for this component.
     */
    void setType(AIType type);

    /**
     * @brief Get the elapsed time since the last update.
     *
     * @return float The elapsed time in seconds.
     */
    float getElapsedTime();

    /**
     * @brief Sets the elapsed time for the AI component.
     *
     * This function updates the internal state of the AI component with the
     * provided elapsed time. It is typically used to keep track of the time
     * that has passed since the last update, allowing the AI to make decisions
     * based on the passage of time.
     *
     * @param elapsedTime The amount of time that has passed, in seconds.
     */
    void setElapsedTime(float elapsedTime);

    /**
     * @brief Updates the AI component based on the specified AI type and elapsed time.
     *
     * @param type The type of AI to update.
     * @param elapsedTime The time elapsed since the last update, in seconds.
     */
    void update(AIType type, float elapsedTime);

  private:
    /**
     * @brief Represents the type of AI for the component.
     *
     * This member variable holds the type of AI that is associated with the component.
     * It is used to determine the behavior and decision-making process of the AI.
     */
    AIType _type;

    /**
     * @brief Stores the elapsed time since the last update.
     */
    float _elapsedTime;
  };
}