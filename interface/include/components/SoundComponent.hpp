/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#pragma once

#include <SFML/Audio.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class SoundComponent : public AComponent {
public:
  SoundComponent(uint32_t entityID, const std::string &soundFilePath);

  /**
   * @brief Destroys the SoundComponent object.
   */
  ~SoundComponent() = default;

  /**
   * @brief Checks if the sound is currently playing.
   *
   * @return true if the sound is playing, false otherwise.
   */
  bool isPlaying() { return _sound.getStatus() == sf::Sound::Playing; }

  /**
   * @brief Plays the sound associated with this component.
   */
  void play() { _sound.play(); }

  /**
   * @brief Stops the currently playing sound.
   *
   * This function halts any sound that is currently being played by the
   * SoundComponent. It calls the stop method on the underlying sound object.
   */
  void stop() { _sound.stop(); }

  /**
   * @brief Updates the sound component.
   *
   * This function is called to update the state of the sound component.
   * It is typically called once per frame with the time elapsed since the last
   * frame.
   *
   * @param deltaTime The time elapsed since the last frame, in seconds.
   */
  void update(std::string &path) {
    _soundBuffer.loadFromFile(path);
    _sound.setBuffer(_soundBuffer);
  }

private:
  /**
   * @brief Holds the sound buffer data for the sound component.
   *
   * This member variable stores the sound buffer which contains the audio data
   * that can be played by the sound component. It is used to load and manage
   * audio resources.
   */
  sf::SoundBuffer _soundBuffer;

  /**
   * @brief Represents a sound component in the ECS (Entity Component System).
   *
   * This component encapsulates an sf::Sound object, which is used to play
   * audio in the game. The sf::Sound class provides functionalities to control
   * the playback of sound effects.
   *
   * @see sf::Sound
   */
  sf::Sound _sound;
};
} // namespace component
