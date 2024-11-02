/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicComponent
*/

#pragma once

#include <r-type/IAudio.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class MusicComponent : public AComponent {
public:
  /**
   * @brief Constructs a new MusicComponent object.
   *
   * @param entityID The unique identifier for the entity associated with this component.
   * @param soundFilePath The file path to the sound file to be used by this component.
   */
  MusicComponent(uint32_t entityID, const std::string &soundFilePath, std::shared_ptr<IAudio> audio);

  /**
   * @brief Destroys the MusicComponent object.
   */
  ~MusicComponent() = default;

  /**
   * @brief Get the music object.
   *
   * @return sf::Music& The music object.
   */
  size_t getMusic() { return _music; }

  /**
   * @brief Play the music.
   */
  void play(std::shared_ptr<IAudio> audio) { audio->playMusic(_music); }

  /**
   * @brief Stop the music.
   */
  void stop(std::shared_ptr<IAudio> audio) { audio->stopMusic(_music); }

  /**
   * @brief Checks if the music is currently playing.
   *
   * @return true if the music is playing, false otherwise.
   */
  bool isPlaying(std::shared_ptr<IAudio> audio) { return audio->isMusicPlaying(_music); }

  void setShouldPlay(bool shouldPlay) { _shouldPlay = shouldPlay; }

  bool getShouldPlay() { return _shouldPlay; }

  std::string getPath() { return _soundFilePath; }

private:
  /**
   * @brief Represents the music object.
   */
  size_t _music;

  bool _shouldPlay;

  std::string _soundFilePath;
};
} // namespace component