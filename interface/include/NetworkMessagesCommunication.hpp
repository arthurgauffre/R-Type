/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkMessages
*/

#pragma once

#include <cstdint>

enum class NetworkMessages : uint32_t {
  ServerAcceptance,
  ServerDenial,
  ServerPing,
  MessageAll,
  ServerMessage,
  ClientConnection,
  createEntity,
  destroyEntity,
  updateEntity,
};

enum class NetworkStatusComponent : uint32_t {
  creation,
  updated,
  deleted,
};

enum class NetworkComponents : uint32_t {
  Texture,
  Position,
  Velocity,
  Health,
  Damage,
  hitbox,
  music,
  sound,
  sprite,
  transform,
  background,
  scroll,
  parent,
};

struct TextureComponent {
  std::string texturePath;
};

struct PositionComponent {
  float x;
  float y;
};

struct VelocityComponent {
  float x;
  float y;
};

struct ParentComponent {
  uint32_t parentID;
};

struct ScrollComponent {
  float x;
  float y;
};

struct HealthComponent {
  int health;
};

struct DamageComponent {
  int damage;
};

struct HitboxComponent {
  float x;
  float y;
};

struct MusicComponent {
  std::string musicPath;
};

struct SoundComponent {
  std::string soundPath;
};

struct SpriteComponent {
  float x;
  float y;
};

struct TransformComponent {
  float x;
  float y;
  float scaleX;
  float scaleY;
};

struct BackgroundComponent {
  std::string texturePath;
  float x;
  float y;
};
