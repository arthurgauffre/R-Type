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
  /**
   * @brief Constructs a new WeaponSystem object.
   *
   * @param componentManager Reference to the ComponentManager.
   * @param entityManager Reference to the EntityManager.
   * @param graphic Shared pointer to an IGraphic object.
   * @param stringCom StringCom object.
   */
  WeaponSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom);

  /**
   * @brief Destructor for the WeaponSystem class.
   *
   * This destructor is responsible for cleaning up any resources
   * that the WeaponSystem class may have allocated during its lifetime.
   */
  ~WeaponSystem();

  /**
   * @brief Updates the weapon system.
   *
   * @param deltaTime The time elapsed since the last update.
   * @param entities A vector of shared pointers to entities that are part of the system.
   * @param msgToSend A reference to a vector of pairs containing actions and their corresponding entity IDs to be sent.
   * @param msgReceived A reference to a vector of pairs containing messages and their corresponding sender and receiver IDs.
   * @param entityMutex A reference to a mutex for synchronizing access to entities.
   * @param sceneStatus A shared pointer to the current scene status.
   */
  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

  /**
   * @brief Initializes the weapon system.
   *
   * This method is called to set up any necessary state or resources
   * for the weapon system. Currently, it does not perform any actions.
   */
  void initialize() override {}

  /**
   * @brief Handles the components associated with the weapon system.
   *
   * This function is an override of the base class method and is responsible
   * for managing the components related to the weapon system. Currently,
   * it does not perform any operations.
   */
  void handleComponents() override {}

private:
  /**
   * @brief Creates a projectile entity with the specified parameters.
   *
   * @param parentID The ID of the parent entity that is creating the projectile.
   * @param texturePath The file path to the texture to be used for the projectile.
   * @param velocity A pair representing the velocity (x, y) of the projectile.
   * @param scale A pair representing the scale (width, height) of the projectile.
   * @param damage The amount of damage the projectile will inflict.
   */
  void createProjectile(uint32_t parentID, std::string texturePath,
                        std::pair<float, float> velocity,
                        std::pair<float, float> scale, int damage);
};
} // namespace ECS_system