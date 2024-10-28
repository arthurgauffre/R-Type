/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TransformComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <utility>

namespace component {
class TransformComponent : public AComponent {
public:
  TransformComponent(uint32_t entityID, std::pair<float, float> position,
                     std::pair<float, float> scale = {1.0f, 1.0f},
                     float rotation = 0.0f);

  /**
   * @brief Default destructor for the TransformComponent class.
   */
  ~TransformComponent() = default;

  /**
   * @brief Retrieves the current position of the component.
   *
   * @return A std::pair containing the x and y coordinates of the position.
   */
  std::pair<float, float> getPosition() { return _position; }

  std::pair<float, float> getPreviousPosition() { return _previousPosition; }

  void setPreviousPosition(std::pair<float, float> position) {
    _previousPosition = position;
  }

  /**
   * @brief Sets the position of the transform component.
   *
   * @param position A constant reference to an std::pair <float, float>
   * representing the new position.
   */
  void setPosition(const std::pair<float, float> &position) {
    _position = position;
  }

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
   * @return std::pair <float, float> The current scale as a 2D vector.
   */
  std::pair<float, float> getScale() { return _scale; }

  /**
   * @brief Sets the scale of the transform component.
   *
   * @param scale A constant reference to an std::pair <float, float>
   * representing the new scale.
   */
  void setScale(const std::pair<float, float> &scale) { _scale = scale; }

  /**
   * @brief Update the transform component.
   *
   * This function is called to update the transform component based on the
   * elapsed time.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void update(std::pair<float, float> position,
                     std::pair<float, float> scale,
                     float rotation = 0) {
    _position = position;
    _scale = scale;
    _rotation = rotation;
  };

private:
  /**
   * @brief Represents the position of the component in 2D space.
   *
   * The position is stored as a pair of floating-point values,
   * where the first element represents the x-coordinate and
   * the second element represents the y-coordinate.
   */
  std::pair<float, float> _position;

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
   * This pair contains two float values representing the scale factors
   * along the x and y axes respectively.
   */
  std::pair<float, float> _scale;

  std::pair<float, float> _previousPosition;
};
} // namespace component