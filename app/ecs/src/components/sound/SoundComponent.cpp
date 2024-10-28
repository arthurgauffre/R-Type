/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#include <components/SoundComponent.hpp>

/**
 * @brief Constructs a new SoundComponent object.
 *
 * This constructor initializes a SoundComponent with the given entity ID and
 * sound file path. It attempts to load the sound from the specified file path
 * into a sound buffer. If the sound file cannot be loaded, it throws a runtime
 * error.
 *
 * @param entityID The ID of the entity associated with this component.
 * @param soundFilePath The file path to the sound file to be loaded.
 *
 * @throws std::runtime_error If the sound file cannot be loaded.
 */
component::SoundComponent::SoundComponent(uint32_t entityID,
                                          const std::string &soundFilePath)
    : AComponent(entityID) {
  if (!_soundBuffer.loadFromFile(soundFilePath))
    throw std::runtime_error("Failed to load sound from file");
  _sound.setBuffer(_soundBuffer);
  _shouldPlay = false;
}