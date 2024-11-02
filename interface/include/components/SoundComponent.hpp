/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#pragma once

#include <r-type/IAudio.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class SoundComponent : public AComponent {
public:
  SoundComponent(uint32_t entityID, const std::string &soundFilePath, std::shared_ptr<IAudio> audio);

  /**
   * @brief Destroys the SoundComponent object.
   */
  ~SoundComponent() = default;

  /**
   * @brief Checks if the sound is currently playing.
   *
   * @return true if the sound is playing, false otherwise.
   */
  bool isPlaying(std::shared_ptr<IAudio> audio) { return audio->isSoundPlaying(_sound); }

  /**
   * @brief Plays the sound associated with this component.
   */
  void play(std::shared_ptr<IAudio> audio) { audio->playSound(_sound); }

  /**
   * @brief Stops the currently playing sound.
   *
   * This function halts any sound that is currently being played by the
   * SoundComponent. It calls the stop method on the underlying sound object.
   */
  void stop(std::shared_ptr<IAudio> audio) { audio->stopSound(_sound); }

  /**
   * @brief Sets the flag indicating whether the sound should play.
   *
   * @param shouldPlay A boolean value where true means the sound should play and false means it should not.
   */
  void setShouldPlay(bool shouldPlay) { _shouldPlay = shouldPlay; }

  /**
   * @brief Checks if the sound should be played.
   *
   * @return true if the sound should be played, false otherwise.
   */
  bool getShouldPlay() { return _shouldPlay; }

  size_t getSound() { return _sound; }

  std::string getPath() { return _soundFilePath; }

private:

  /**
   * @brief Represents a sound component in the ECS (Entity Component System).
   *
   * This component encapsulates an sf::Sound object, which is used to play
   * audio in the game. The sf::Sound class provides functionalities to control
   * the playback of sound effects.
   *
   * @see sf::Sound
   */
  size_t _sound;

  /**
   * @brief Indicates whether the sound should be played.
   *
   * This boolean member variable is used to determine if the sound associated
   * with this component should be played. When set to true, the sound will
   * play; when set to false, the sound will not play.
   */
  bool _shouldPlay;

  std::string _soundFilePath;
};
} // namespace component
