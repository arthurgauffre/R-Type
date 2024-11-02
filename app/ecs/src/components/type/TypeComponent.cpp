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
 * @param type The type associated with this component.
 */
component::TypeComponent::TypeComponent(uint32_t entityID, Type type)
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
 * @return Type The type of the component.
 */
Type component::TypeComponent::getType() { return _type; }

/**
 * @brief Sets the type of the component.
 *
 * @param type The new type to be set for the component.
 */
void component::TypeComponent::setType(Type type) { _type = type; }
