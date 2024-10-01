/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#include <r-type/SoundComponent.hpp>

component::SoundComponent::SoundComponent(uint32_t entityID,
                                          const std::string &soundFilePath)
    : AComponent(entityID) {
  if (!_soundBuffer.loadFromFile(soundFilePath))
    throw std::runtime_error("Failed to load sound from file");
  _sound.setBuffer(_soundBuffer);
}