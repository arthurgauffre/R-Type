/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#pragma once

#include "AComponent.hpp"
#include <SFML/Audio.hpp>

namespace component
{
    class SoundComponent : public AComponent
    {
    public:
        SoundComponent(uint32_t entityID, const std::string &soundFilePath);
        ~SoundComponent() = default;

        bool isPlaying() { return _sound.getStatus() == sf::Sound::Playing; } // Check if the sound is playing
        void play() { _sound.play(); }                                        // Play the sound
        void stop() { _sound.stop(); }                                        // Pause the sound
        void update(float deltaTime) override {}                              // Update the component

    private:
        sf::SoundBuffer _soundBuffer;
        sf::Sound _sound;
    };
}
