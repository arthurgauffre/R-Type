/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enum
**
** This header file contains various enumerations used throughout the R-Type project.
** Each enumeration represents a different category of constants that are used to 
** manage game scenes, actions, AI types, texture paths, text fonts, text strings, 
** sound paths, entity types, and keyboard inputs.
**
** Enumerations:
** - Scene: Represents different scenes in the game (e.g., MENU, GAME, GAMEOVER).
** - Action: Represents different actions that can be performed (e.g., MOVE_UP, SHOOT, EXIT).
** - AIType: Represents different types of AI behaviors (e.g., LINEAR, SINUSOIDAL).
** - TexturePath: Represents different texture paths for game assets (e.g., Player, Enemy).
** - TextFont: Represents different text fonts used in the game (e.g., Arial).
** - TextString: Represents different text strings used in the game (e.g., Play, Menu).
** - SoundPath: Represents different sound paths for game audio (e.g., Shoot, BackgroundMusic).
** - Type: Represents different types of game entities (e.g., PLAYER, ENEMY, WEAPON).
** - KeyBoard: Represents different keyboard inputs (e.g., A, B, C, Space, escape).
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
    Structure,
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

enum class SoundPath : uint32_t
{
    Shoot,
    BackgroundMusic,
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