/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponComponent
*/

#include <components/WeaponComponent.hpp>

component::WeaponComponent::WeaponComponent(uint32_t entityID, std::string type, float cooldown, int damage)
    : AComponent(entityID), _type(type), _cooldown(cooldown), _damage(damage), _lastFireTime(0), _isFiring(false)
{
}

component::WeaponComponent::~WeaponComponent()
{
}

void component::WeaponComponent::setCooldown(float cooldown)
{
    _cooldown = cooldown;
}

float component::WeaponComponent::getCooldown()
{
    return _cooldown;
}

void component::WeaponComponent::setLastFireTime(float lastFireTime)
{
    _lastFireTime = lastFireTime;
}

float component::WeaponComponent::getLastFireTime()
{
    return _lastFireTime;
}

void component::WeaponComponent::setType(std::string type)
{
    _type = type;
}

std::string component::WeaponComponent::getType()
{
    return _type;
}

void component::WeaponComponent::setIsFiring(bool isFiring)
{
    _isFiring = isFiring;
}

bool component::WeaponComponent::getIsFiring()
{
    return _isFiring;
}

void component::WeaponComponent::setDamage(int damage)
{
    _damage = damage;
}

int component::WeaponComponent::getDamage()
{
    return _damage;
}
