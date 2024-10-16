/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** VelocityComponent
*/

#pragma once

#include <SFML/System/Vector2.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class VelocityComponent : public AComponent {
public:
  /**
   * @brief Constructs a new VelocityComponent object.
   *
   * @param entityID The ID of the entity associated with this component.
   * @param velocity The initial velocity of the entity.
   */
  VelocityComponent(uint32_t entityID, sf::Vector2f velocity = {0, 0},
                    sf::Vector2f actualVelocity = {0, 0});
  /**
   * @brief Default destructor for the VelocityComponent class.
   */
  ~VelocityComponent() = default;

  /**
   * @brief Get the velocity of the entity.
   *
   * @return The velocity as a 2D vector.
   */
  sf::Vector2f getVelocity() const { return _velocity; }

  /**
   * @brief Set the velocity of the entity.
   *
   * @param velocity The new velocity as a 2D vector.
   */
  void setVelocity(const sf::Vector2f &velocity) { _velocity = velocity; }

  void setActualVelocityX(const float x) { _actualVelocity.x = x; }
  void setActualVelocityY(const float y) { _actualVelocity.y = y; }
  sf::Vector2f getActualVelocity() { return _actualVelocity; }

  void update(float deltaTime) override{};

private:
  sf::Vector2f _velocity;

  sf::Vector2f _actualVelocity;
};
} // namespace component