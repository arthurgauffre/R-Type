/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitBoxComponent
*/

#pragma once

#include "AComponent.hpp"

namespace component {
class HitBoxComponent : public AComponent {
public:
  /**
   * @brief Constructs a new HitBoxComponent object.
   *
   * @param entityID The ID of the entity this component is associated with.
   * @param width The width of the hitbox.
   * @param height The height of the hitbox.
   */
  HitBoxComponent(uint32_t entityID, float width, float height)
      : AComponent(entityID), _width(width), _height(height){};

  /**
   * @brief Destroys the HitBoxComponent object.
   */
  ~HitBoxComponent() = default;

  /**
   * @brief Get the width of the hitbox.
   *
   * @return float The width of the hitbox.
   */
  float getWidth() const { return _width; }

  /**
   * @brief Get the height of the hitbox.
   *
   * @return float The height of the hitbox.
   */
  float getHeight() const { return _height; }

  /**
   * @brief Updates the HitBoxComponent.
   *
   * This function is called to update the state of the HitBoxComponent.
   * It is typically called once per frame and allows the component to
   * perform any necessary updates based on the elapsed time since the
   * last update.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void update(float deltaTime) override{};

private:
  /**
   * @brief Represents the width of the hitbox.
   */
  float _width;

  /**
   * @brief Represents the height of the hitbox.
   */
  float _height;
};
} // namespace component