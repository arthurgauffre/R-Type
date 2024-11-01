/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enum
*/

#pragma once
#include <cstdint>

enum class Scene : uint32_t
{
    MENU,
    GAME,
    GAMEOVER,
    SETTINGS,
    LOADING,
    NONE
};

enum class Action : uint32_t
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOOT,
    MENU,
    PLAY,
    GAME,
    EXIT,
    NONE,
};

enum class AIType : uint32_t
{
    LINEAR,
    SINUSOIDAL,
    CIRCULAR,
    UNKNOWN,
};

enum class TexturePath : uint32_t
{
    Player,
    Enemy,
    Background,
    Bullet,
    Unknown,
};

enum class TextFont : uint32_t
{
    Arial,
    Unknown,
};

enum class TextString : uint32_t
{
    Play,
    Unknown,
};

enum class Type
{
    PLAYER,
    ENEMY,
    WEAPON,
    PROJECTILE,
    PLAYER_PROJECTILE,
    ENEMY_PROJECTILE,
    BACKGROUND,
    UNKNOWN,
    STRUCTURE,
};

enum class KeyBoard : uint32_t
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Space,
    Unknown,
};