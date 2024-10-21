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
  void update(float deltaTime) override;

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