/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TypeComponent
*/

#include <components/TypeComponent.hpp>

component::TypeComponent::TypeComponent(uint32_t entityID, Type type)
    : AComponent(entityID), _type(type) {}

component::TypeComponent::~TypeComponent() {}

component::Type component::TypeComponent::getType() { return _type; }

void component::TypeComponent::setType(Type type) { _type = type; }