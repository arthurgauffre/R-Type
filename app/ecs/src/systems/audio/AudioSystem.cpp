/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AudioSystem
*/

#include "AudioSystem.hpp"

/**
 * @brief Updates the audio system by processing sound and music components of
 * entities.
 *
 * This function iterates through a list of entities and checks for the presence
 * of SoundComponent and MusicComponent in each entity. If a SoundComponent or
 * MusicComponent is found and is marked as playing, the respective play
 * function is called.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be processed.
 */
void ECS_system::AudioSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity : entities) {
    component::SoundComponent *soundComponent =
        _componentManager.getComponent<component::SoundComponent>(
            entity->getID());
    component::MusicComponent *musicComponent =
        _componentManager.getComponent<component::MusicComponent>(
            entity->getID());

    if (soundComponent) {
      if (!soundComponent->isPlaying())
        soundComponent->play();
    }
    if (musicComponent) {
      if (!musicComponent->isPlaying())
        musicComponent->play();
    }
  }
}