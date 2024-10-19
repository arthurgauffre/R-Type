/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** VelocityComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
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
    VelocityComponent(uint32_t entityID, std::pair<float, float> velocity = {0, 0},
                      std::pair<float, float> actualVelocity = {0, 0});
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
    void setVelocity(const std::pair<float, float> &velocity) { _velocity = velocity; }

    void setActualVelocityX(const float x) { _actualVelocity.first = x; }
    void setActualVelocityY(const float y) { _actualVelocity.second = y; }
    std::pair<float, float> getActualVelocity() { return _actualVelocity; }

    void update(float deltaTime) override {};

  private:
    std::pair<float, float> _velocity;

    std::pair<float, float> _actualVelocity;
  };
} // namespace component