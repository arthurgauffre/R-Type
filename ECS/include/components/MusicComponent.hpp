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

        /**
         * @brief Destroys the MusicComponent object.
         */
        ~MusicComponent() = default;

        /**
         * @brief Sets the music from the specified file path.
         *
         * This function attempts to open and load a music file from the given path.
         * If the file cannot be opened, it throws a runtime error.
         *
         * @param path The file path to the music file.
         * @throws std::runtime_error If the music file cannot be loaded.
         */
        void setMusic(const std::string &path)
        {
            if (!_music.openFromFile(path))
                throw std::runtime_error("Failed to load music from file: " + path);
        }

        /**
         * @brief Get the music object.
         *
         * @return sf::Music& The music object.
         */
        sf::Music &getMusic() { return _music; }

        /**
         * @brief Updates the MusicComponent.
         *
         * This function is called to update the state of the MusicComponent.
         * It is typically called once per frame and allows the component to
         * perform any necessary updates based on the elapsed time since the
         * last update.
         *
         * @param deltaTime The time elapsed since the last update, in seconds.
         */
        void update(float deltaTime) override {}

        /**
         * @brief Play the music.
         */
        void play() { _music.play(); }

        /**
         * @brief Stop the music.
         */
        void stop() { _music.stop(); }

        /**
         * @brief Checks if the music is currently playing.
         *
         * @return true if the music is playing, false otherwise.
         */
        bool isPlaying() { return _music.getStatus() == sf::Music::Playing; }

        /**
         * @brief Sets the looping state of the music.
         *
         * This function enables or disables the looping of the music. When looping is enabled,
         * the music will restart from the beginning once it reaches the end.
         *
         * @param loop A boolean value indicating whether the music should loop (true) or not (false).
         */
        void setLoop(bool loop) { _music.setLoop(loop); }

    private:
        /**
         * @brief Represents the music object.
         */
        sf::Music _music;
    };
}