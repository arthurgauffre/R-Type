/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TypeComponent
*/

#include <components/TypeComponent.hpp>

/**
 * @brief Constructs a new TypeComponent object.
 *
 * @param entityID The unique identifier for the entity.
 * @param type The type of the component.
 */
component::TypeComponent::TypeComponent(uint32_t entityID, std::string type)
    : AComponent(entityID), _type(type) {}

/**
 * @brief Destructor for the TypeComponent class.
 *
 * This destructor is responsible for cleaning up any resources
 * allocated by the TypeComponent instance. It ensures that all
 * necessary cleanup operations are performed when a TypeComponent
 * object is destroyed.
 */
component::TypeComponent::~TypeComponent() {}

/**
 * @brief Retrieves the type of the component.
 *
 * @return A string representing the type of the component.
 */
std::string component::TypeComponent::getType() { return _type; }

/**
 * @brief Sets the type of the component.
 *
 * This function assigns a new type to the component.
 *
 * @param type A string representing the new type to be set.
 */
void component::TypeComponent::setType(std::string type) { _type = type; }