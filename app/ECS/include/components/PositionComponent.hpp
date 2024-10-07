/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PositionComponent
*/

#pragma once

#include "AComponent.hpp"

#include <SFML/Graphics.hpp>
namespace component
{
  class PositionComponent : public AComponent
  {
  public:
    /**
     * @brief Constructs a new PositionComponent object.
     *
     * @param entityID The unique identifier for the entity.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    PositionComponent(uint32_t entityID, float x, float y)
        : AComponent(entityID), _position(x, y) {};
    /**
     * @brief Default destructor for the PositionComponent class.
     */
    ~PositionComponent() = default;

    /**
     * @brief Get the X coordinate.
     *
     * @return The X coordinate as a float.
     */
    float getX() const { return _position.x; }

    /**
     * @brief Sets the x-coordinate of the position.
     *
     * @param x The new x-coordinate value to be set.
     */
    void setX(float x) { _position.x = x; }

    /**
     * @brief Get the Y coordinate of the position.
     *
     * @return The Y coordinate as a float.
     */
    float getY() const { return _position.y; }

    /**
     * @brief Sets the y-coordinate of the position.
     *
     * @param y The new y-coordinate value to be set.
     */
    void setY(float y) { _position.y = y; }

    /**
     * @brief Updates the position component.
     *
     * This function is called to update the position component based on the
     * elapsed time.
     *
     * @param deltaTime The time elapsed since the last update, in seconds.
     */
    void update(float deltaTime) override {};

  private:
    /**
     * @brief Represents a 2D vector for position.
     *
     * This component stores the position of an entity in a 2D space using
     * the SFML library's sf::Vector2f class, which contains x and y coordinates.
     */
    sf::Vector2f _position;
  };
} // namespace component