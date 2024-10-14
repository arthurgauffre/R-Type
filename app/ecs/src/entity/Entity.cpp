/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Entity
*/

#include <r-type/Entity.hpp>

namespace entity {
entity::Entity::Entity(uint32_t id) : id(id), isActive(true) {}

entity::Entity::~Entity() = default;

uint32_t entity::Entity::getID() const { return id; }

void entity::Entity::setActive(bool active) { isActive = active; }

bool entity::Entity::getActive() const { return isActive; }
} // namespace entity
