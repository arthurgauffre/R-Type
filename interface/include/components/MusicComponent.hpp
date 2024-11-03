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
   * @return size_t id The music object.
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

  /**
   * @brief Sets the playback state of the music component.
   * 
   * This function allows you to control whether the music should be playing or not.
   * 
   * @param shouldPlay A boolean value indicating whether the music should play (true) or stop (false).
   */
  void setShouldPlay(bool shouldPlay) { _shouldPlay = shouldPlay; }

  /**
   * @brief Get the status of whether the music should play.
   * 
   * @return true if the music should play, false otherwise.
   */
  bool getShouldPlay() { return _shouldPlay; }

  /**
   * @brief Retrieves the file path of the sound file associated with this component.
   * 
   * @return std::string The file path of the sound file.
   */
  std::string getPath() { return _soundFilePath; }

private:
  /**
   * @brief Represents the musicID object.
   */
  size_t _music;

  /**
   * @brief Indicates whether the music should be played.
   */
  bool _shouldPlay;

  /**
   * @brief Path to the sound file.
   */
  std::string _soundFilePath;
};
} // namespace component