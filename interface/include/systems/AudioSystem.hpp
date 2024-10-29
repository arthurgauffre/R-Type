/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AudioSystem
*/

#pragma once

#include <components/MusicComponent.hpp>
#include <components/SoundComponent.hpp>
#include <r-type/ASystem.hpp>

namespace ECS_system {
class AudioSystem : virtual public ASystem {
public:
  /**
   * @class AudioSystem
   * @brief A system responsible for managing audio components within the ECS
   * framework.
   *
   * The AudioSystem class inherits from ASystem and is responsible for handling
   * audio-related components in the entity-component-system (ECS) architecture.
   *
   * @param componentManager A reference to the ComponentManager that manages
   * all components.
   */
  AudioSystem(component::ComponentManager &componentManager,
              entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}

  /**
   * @brief Destroys the AudioSystem object.
   */
  ~AudioSystem() = default;

  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex) override;

  void initialize() override{};

  /**
   * @brief Handles the audio components within the ECS framework.
   *
   * This function is an override of the base class method and is responsible
   * for managing and updating the audio components in the system. The actual
   * implementation details should be provided in the function body.
   */
  void handleComponents() override{};

private:
};
} // namespace ECS_system