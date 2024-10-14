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

/* typedef struct WeaponSystemData {
  int damage;
  float velocity;
  sf::Vector2f position;
  std::string texturePath;
  sf::Vector2f spriteSize;
} WeaponSystemData; */

class WeaponSystem : virtual public ASystem {
public:
  WeaponSystem(component::ComponentManager &componentManager);
  ~WeaponSystem();

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities) override;
  void initialize() override {}
  void handleComponents() override {}

  void addWeapon(uint32_t entityID, int damage, float velocity,
                 sf::Vector2f position, std::string texturePath,
                 sf::Vector2f spriteSize);
  void removeWeapon(uint32_t entityID);

private:
};
} // namespace ECS_system