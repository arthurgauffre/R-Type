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
#include <components/HitBoxComponent.hpp>
#include <components/ParentComponent.hpp>
#include <components/PositionComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/VelocityComponent.hpp>
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

private:
  void createProjectile(uint32_t parentID, std::string texturePath,
                        sf::Vector2f velocity, sf::Vector2f scale, int damage);
};
} // namespace ECS_system