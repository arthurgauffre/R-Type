/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clock
*/

#pragma once

#include <iostream>
#include <chrono>

namespace rtype
{
    class Clock
    {
    public:
        Clock();
        ~Clock() = default;

        double getElapsedTime() const;

        double restart();

    private:
        std::chrono::steady_clock::time_point startTime;
    };
}