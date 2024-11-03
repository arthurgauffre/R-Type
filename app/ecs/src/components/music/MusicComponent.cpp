/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicComponent
*/

#include <components/MusicComponent.hpp>

/**
 * @brief Constructs a new MusicComponent object.
 *
 * This constructor initializes a MusicComponent with the given entity ID and
 * attempts to load a music file from the specified file path. If the music
 * file cannot be loaded, it throws a runtime error.
 *
 * @param entityID The ID of the entity associated with this component.
 * @param soundFilePath The file path to the music file to be loaded.
 *
 * @throws std::runtime_error If the music file cannot be loaded.
 */
component::MusicComponent::MusicComponent(uint32_t entityID,
                                          const std::string &soundFilePath,
                                          std::shared_ptr<IAudio> audio)
    : AComponent(entityID) {
  _soundFilePath = soundFilePath;
  _music = audio->createMusic(soundFilePath);
}
