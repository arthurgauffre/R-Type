/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SizeComponent
*/

#include <components/SizeComponent.hpp>

/**
 * @brief Constructs a new SizeComponent object.
 *
 * @param entityID The unique identifier for the entity.
 * @param size A pair representing the width and height of the component.
 */
component::SizeComponent::SizeComponent(uint32_t entityID,
                                        std::pair<float, float> size)
    : AComponent(entityID), _size(size) {}

/**
 * @brief Destroys the SizeComponent object.
 */
component::SizeComponent::~SizeComponent() {}

/**
 * @brief Sets the size of the component.
 *
 * This function sets the size of the component to the specified value.
 *
 * @param size A pair representing the width and height of the component.
 */
void component::SizeComponent::setSize(const std::pair<float, float> &size) {
  this->_size = size;
}

/**
 * @brief Retrieves the size of the component.
 *
 * This function returns the size of the component as a pair representing the
 * width and height.
 *
 * @return const std::pair<float, float> The size of the component.
 */
const std::pair<float, float> component::SizeComponent::getSize() {
  return this->_size;
}