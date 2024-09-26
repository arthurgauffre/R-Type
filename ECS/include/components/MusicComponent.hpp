/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicComponent
*/

#pragma once

#include "AComponent.hpp"
#include <SFML/Audio.hpp>

namespace component
{
    class MusicComponent : public AComponent
    {
    public:
        MusicComponent(uint32_t entityID, const std::string &soundFilePath);
        ~MusicComponent() = default;

        void setMusic(const std::string &path) { _music.openFromFile(path); } // Load music from file
        sf::Music &getMusic() { return _music; }                              // Return the music
        void update(float deltaTime) override {}                              // Update the component
        void play() { _music.play(); }                                        // Play the music
        void stop() { _music.stop(); }                                        // Pause the music
        bool isPlaying() { return _music.getStatus() == sf::Music::Playing; } // Check if the music is playing
        void setLoop(bool loop) { _music.setLoop(loop); }                     // Set the music to loop

    private:
        sf::Music _music; // Music object
    };
}