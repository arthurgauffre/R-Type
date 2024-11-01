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
#include <components/SoundComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/VelocityComponent.hpp>
#include <components/WeaponComponent.hpp>

#include <unordered_map>
#include <vector>

namespace ECS_system {

class WeaponSystem : virtual public ASystem {
public:
  WeaponSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, StringCom stringCom);
  ~WeaponSystem();

  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;
  void initialize() override {}
  void handleComponents() override {}

private:
  void createProjectile(uint32_t parentID, std::string texturePath,
                        std::pair<float, float> velocity,
                        std::pair<float, float> scale, int damage);
};
} // namespace ECS_system