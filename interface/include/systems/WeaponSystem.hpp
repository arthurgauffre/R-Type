/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

#include <components/CooldownComponent.hpp>
#include <components/DamageComponent.hpp>
#include <components/ParentComponent.hpp>
#include <components/WeaponComponent.hpp>

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
  WeaponSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager);
  ~WeaponSystem();

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities) override;
  void initialize() override {}
  void handleComponents() override {}

  void createProjectile(uint32_t entityID, std::string texturePath,
                        sf::Vector2f position, sf::Vector2f velocity,
                        sf::Vector2f scale, int damage);

private:
};
} // namespace ECS_system