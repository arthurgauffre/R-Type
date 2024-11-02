/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AAudio
*/

#pragma once

#include <r-type/IAudio.hpp>

class AAudio : public IAudio {
    public:
        AAudio(): IAudio(){};
        virtual ~AAudio() = default;

        virtual size_t createSound(const std::string &path) = 0;
        virtual size_t createMusic(const std::string &path) = 0;

        virtual void playSound(size_t id) = 0;
        virtual void playMusic(size_t id) = 0;

        virtual void stopSound(size_t id) = 0;
        virtual void stopMusic(size_t id) = 0;

        virtual bool isSoundPlaying(size_t id) = 0;
        virtual bool isMusicPlaying(size_t id) = 0;

    protected:
    private:
};
