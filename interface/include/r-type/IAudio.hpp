/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IAudio
*/

#pragma once

#ifdef _WIN32
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C"
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include <r-type/Enum.hpp>


class IAudio {
    public:
        IAudio(){};
        virtual ~IAudio() = default;

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
        std::unordered_map<std::string, size_t> _soundsId;
        std::unordered_map<std::string, size_t> _musicsId;
};
