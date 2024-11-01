/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** VelocityComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <iostream>
#include <utility>

namespace component
{
  class VelocityComponent : public AComponent
  {
  public:
    /**
     * @brief Constructs a new VelocityComponent object.
     *
     * @param entityID The ID of the entity associated with this component.
     * @param velocity The initial velocity of the entity.
     */
    VelocityComponent(uint32_t entityID,
                      std::pair<float, float> velocity = {0.0f, 0.0f},
                      std::pair<float, float> actualVelocity = {0.0f, 0.0f});

    /**
     * @brief Default destructor for the VelocityComponent class.
     */
    ~VelocityComponent() = default;

    /**
     * @brief Get the velocity of the entity.
     *
     * @return The velocity as a 2D vector.
     */
    std::pair<float, float> getVelocity() const { return _velocity; }

    /**
     * @brief Set the velocity of the entity.
     *
     * @param velocity The new velocity as a 2D vector.
     */
    void setVelocity(const std::pair<float, float> &velocity)
    {
      _velocity = velocity;
    }

    /**
     * @brief Sets the actual velocity in the X direction.
     *
     * This function updates the X component of the actual velocity.
     *
     * @param x The new velocity value for the X direction.
     */
    void setActualVelocityX(const float x) { _actualVelocity.first = x; }

    /**
     * @brief Sets the actual velocity in the Y direction.
     *
     * This function updates the Y component of the actual velocity.
     *
     * @param y The new velocity value for the Y direction.
     */
    void setActualVelocityY(const float y) { _actualVelocity.second = y; }

    /**
     * @brief Retrieves the current velocity.
     *
     * This function returns the actual velocity as a pair of floats,
     * representing the velocity in the x and y directions respectively.
     *
     * @return std::pair<float, float> The current velocity.
     */
    std::pair<float, float> getActualVelocity() { return _actualVelocity; }

    void update(std::pair<float, float> velocity, std::pair<float, float> actualVelocity)
    {
      _velocity = velocity;
      _actualVelocity = actualVelocity;
      };

  private:
    /**
     * @brief Represents the velocity of an entity.
     *
     * This pair contains two float values representing the velocity
     * in the x and y directions respectively.
     */
    std::pair<float, float> _velocity;

    /**
     * @brief Represents the current velocity of an entity.
     *
     * This pair holds the velocity components in the x and y directions.
     * The first element represents the velocity in the x direction,
     * and the second element represents the velocity in the y direction.
     */
    std::pair<float, float> _actualVelocity;
  };
} // namespace component