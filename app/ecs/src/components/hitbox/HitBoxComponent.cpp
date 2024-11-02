/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitBoxComponent
*/

#include <components/HitBoxComponent.hpp>

/**
 * @brief Construct a new HitBoxComponent object.
 *
 * @param entityID The ID of the entity this component is associated with.
 * @param width The width of the hitbox.
 * @param height The height of the hitbox.
 */
component::HitBoxComponent::HitBoxComponent(uint32_t entityID, float width,
                                            float height)
    : AComponent(entityID), _width(width), _height(height) {
      this->_communication = ComponentCommunication::SERVERONLY;
    }

/**
 * @brief Destructor for the HitBoxComponent class.
 *
 * This destructor is responsible for cleaning up any resources
 * allocated by the HitBoxComponent. It ensures that when an instance
 * of HitBoxComponent is destroyed, all associated resources are properly
 * released.
 */
component::HitBoxComponent::~HitBoxComponent() {}

/**
 * @brief Get the width of the hitbox component.
 *
 * This function returns the width of the hitbox component.
 *
 * @return float The width of the hitbox component.
 */
float component::HitBoxComponent::getWidth() const { return _width; }

/**
 * @brief Retrieves the height of the hitbox component.
 *
 * @return The height of the hitbox as a float.
 */
float component::HitBoxComponent::getHeight() const { return _height; }

/**
 * @brief Updates the dimensions of the hitbox.
 *
 * @param width The new width of the hitbox.
 * @param height The new height of the hitbox.
 */
void component::HitBoxComponent::update(float width, float height) {
  _width = width;
  _height = height;
}
