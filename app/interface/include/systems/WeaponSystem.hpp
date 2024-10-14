/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

#include <components/DamageComponent.hpp>
#include <components/ParentComponent.hpp>

#include <unordered_map>
#include <vector>

namespace ECS_system {
typedef struct WeaponSystemData {
  int damage;
  float velocity;
  sf::Vector2f position;
  std::string texturePath;
  sf::Vector2f spriteSize;
} WeaponSystemData;

class WeaponSystem : virtual public ASystem {
public:
  WeaponSystem(component::ComponentManager &componentManager);
  ~WeaponSystem();

private:
  std::unordered_map<uint32_t, std::vector<WeaponSystemData>> _weaponData;
};
} // namespace ECS_system