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
              entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom)
      : ASystem(componentManager, entityManager, graphic, audio, stringCom) {}

  /**
   * @brief Destroys the AudioSystem object.
   */
  ~AudioSystem() = default;

  /**
   * @brief Updates the audio system.
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
   * @brief Initializes the audio system.
   *
   * This method is called to set up any necessary resources or configurations
   * for the audio system. It overrides the base class implementation.
   */
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