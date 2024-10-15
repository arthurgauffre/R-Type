/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TypeComponent
*/

#include <components/TypeComponent.hpp>

component::TypeComponent::TypeComponent(uint32_t entityID, std::string type)
    : AComponent(entityID), _type(type)
{
}

component::TypeComponent::~TypeComponent()
{
}

std::string component::TypeComponent::getType()
{
    return _type;
}

void component::TypeComponent::setType(std::string type)
{
    _type = type;
}