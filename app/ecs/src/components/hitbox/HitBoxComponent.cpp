/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitBoxComponent
*/

#include <components/HitBoxComponent.hpp>

component::HitBoxComponent::HitBoxComponent(uint32_t entityID, float width, float height)
    : AComponent(entityID), _width(width), _height(height)
{
}

component::HitBoxComponent::~HitBoxComponent()
{
}

float component::HitBoxComponent::getWidth() const
{
    return _width;
}

float component::HitBoxComponent::getHeight() const
{
    return _height;
}

void component::HitBoxComponent::update(float deltaTime)
{
}