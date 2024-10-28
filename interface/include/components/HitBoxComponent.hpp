/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitBoxComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
class HitBoxComponent : public AComponent {
public:
  HitBoxComponent(uint32_t entityID, float width, float height);
  ~HitBoxComponent();

  float getWidth() const;
  float getHeight() const;

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
  void update(float width, float height);

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