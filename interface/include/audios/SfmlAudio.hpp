/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlAudio
*/

#pragma once

#include <SFML/Audio.hpp>
#include <r-type/AAudio.hpp>

class SfmlAudio: public AAudio {
    public:
        SfmlAudio();
        ~SfmlAudio();

        size_t createSound(const std::string &path) override;
        size_t createMusic(const std::string &path) override;

        void updateSound(size_t id, const std::string &path) override;
        void updateMusic(size_t id, const std::string &path) override;

        void playSound(size_t id) override;
        void playMusic(size_t id) override;

        void stopSound(size_t id) override;
        void stopMusic(size_t id) override;

        bool isSoundPlaying(size_t id) override;
        bool isMusicPlaying(size_t id) override;

    protected:
    private:
        std::unordered_map<size_t, std::shared_ptr<sf::Sound>> _sounds;
        std::unordered_map<size_t, std::shared_ptr<sf::SoundBuffer>> _soundBuffers;
        std::unordered_map<size_t, std::shared_ptr<sf::Music>> _musics;
};
