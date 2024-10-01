/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PositionComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
class PositionComponent : public AComponent {
public:
  /**
   * @brief Constructs a new PositionComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param x The x-coordinate of the position.
   * @param y The y-coordinate of the position.
   */
  PositionComponent(uint32_t entityID, float x, float y)
      : AComponent(entityID), _x(x), _y(y){};
  /**
   * @brief Default destructor for the PositionComponent class.
   */
  ~PositionComponent() = default;

  /**
   * @brief Get the X coordinate.
   *
   * @return The X coordinate as a float.
   */
  float getX() const { return _x; }

  /**
   * @brief Get the Y coordinate of the position.
   *
   * @return The Y coordinate as a float.
   */
  float getY() const { return _y; }

  /**
   * @brief Updates the position component.
   *
   * This function is called to update the position component based on the
   * elapsed time.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void update(float deltaTime) override{};

private:
  /**
   * @brief Represents the x-coordinate of the position.
   */
  float _x;

  /**
   * @brief Represents the y-coordinate of the position.
   */
  float _y;
};
} // namespace component