/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enum
*/

#pragma once
#include <cstdint>

enum class Scene: uint32_t {
    MENU,
    GAME,
    GAMEOVER,
    SETTINGS,
    LOADING,
    NONE
};