/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TransformComponent
*/

#pragma once

#include "AComponent.hpp"

#include <SFML/Graphics.hpp>

namespace component {
class TransformComponent : public AComponent {
public:
  /**
   * @brief Construct a new TransformComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param position The initial position of the entity as a 2D vector.
   * @param scale The scale of the entity as a 2D vector. Defaults to
   * {1.0f, 1.0f}.
   */
  TransformComponent(uint32_t entityID, sf::Vector2f position,
                     sf::Vector2f scale = {1.0f, 1.0f})
      : AComponent(entityID), _position(position), _scale(scale),
        _rotation(0.0f){};

  /**
   * @brief Default destructor for the TransformComponent class.
   */
  ~TransformComponent() = default;

  /**
   * @brief Retrieves the current position of the component.
   *
   * @return sf::Vector2f The current position as a 2D vector.
   */
  sf::Vector2f getPosition() { return _position; }

  /**
   * @brief Sets the position of the transform component.
   *
   * @param position A constant reference to an sf::Vector2f representing the
   * new position.
   */
  void setPosition(const sf::Vector2f &position) { _position = position; }

  /**
   * @brief Get the current rotation value.
   *
   * @return float The current rotation in degrees.
   */
  float getRotation() { return _rotation; }

  /**
   * @brief Sets the rotation angle of the component.
   *
   * @param angle The new rotation angle in degrees.
   */
  void setRotation(float angle) { _rotation = angle; }

  /**
   * @brief Retrieves the scale of the transform component.
   *
   * @return sf::Vector2f The current scale as a 2D vector.
   */
  sf::Vector2f getScale() { return _scale; }

  /**
   * @brief Sets the scale of the transform component.
   *
   * @param scale A constant reference to an sf::Vector2f representing the new
   * scale.
   */
  void setScale(const sf::Vector2f &scale) { _scale = scale; }

  /**
   * @brief Update the transform component.
   *
   * This function is called to update the transform component based on the
   * elapsed time.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void update(float deltaTime) override{};

private:
  /**
   * @brief Represents a 2D vector with float coordinates.
   *
   * This class is part of the SFML (Simple and Fast Multimedia Library) and is
   * used to define positions, velocities, and other 2D vector quantities. It
   * contains two public member variables: x and y, which represent the
   * x-coordinate and y-coordinate of the vector, respectively.
   */
  sf::Vector2f _position;

  /**
   * @brief Represents the rotation of the entity in degrees.
   *
   * This value indicates the current rotation angle of the entity.
   * It is measured in degrees and can be used to determine the
   * orientation of the entity in the game world.
   */
  float _rotation;

  /**
   * @brief Represents the scale of the transform component.
   *
   * This member variable stores the scale factors along the x and y axes.
   * It is used to scale the size of the entity in the 2D space.
   */
  sf::Vector2f _scale;
};
} // namespace component