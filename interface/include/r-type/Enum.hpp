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
    KEYBIND,
    ALL,
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
    KEYBIND,
    KEYMOVEUP,
    KEYMOVEDOWN,
    KEYMOVELEFT,
    KEYMOVERIGHT,
    KEYSHOOT,
    PLAY,
    GAME,
    PROTANOPIA,
    DEUTERANOPIA,
    TRITANOPIA,
    CLEARFILTER,
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
    Protanopia,
    Deuteranopia,
    Tritanopia,
    ClearFilter,
    KeyBind,
    Menu,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Shoot,
    PressKey,
    Z,
    S,
    Q,
    D,
    Space,
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
    STRUCTURE,
    FILTER,
    BUTTON,
    BUTTONBIND,
    UNKNOWN,
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
    escape,
    Unknown,
};