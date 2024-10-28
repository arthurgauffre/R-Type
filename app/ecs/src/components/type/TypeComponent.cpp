/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TypeComponent
*/

#include <components/TypeComponent.hpp>

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

component::Type component::TypeComponent::getType() { return _type; }

void component::TypeComponent::setType(Type type) { _type = type; }
