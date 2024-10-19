/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TransformComponent
*/

#include <components/TransformComponent.hpp>

namespace component {
/**
 * @brief Constructs a new TransformComponent object.
 *
 * @param entityID The unique identifier for the entity.
 * @param position A pair of floats representing the position (x, y) of the
 * entity.
 * @param scale A pair of floats representing the scale (width, height) of the
 * entity.
 * @param rotation A float representing the rotation angle of the entity in
 * degrees.
 */
TransformComponent::TransformComponent(uint32_t entityID,
                                       std::pair<float, float> position,
                                       std::pair<float, float> scale,
                                       float rotation)
    : AComponent(entityID), _position(position), _scale(scale),
      _rotation(rotation) {}
} // namespace component
