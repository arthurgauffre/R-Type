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
  deleteEntity,
  updateEntity,
  createTexture,
  createPosition,
  createVelocity,
  createHealth,
  createDamage,
  createHitbox,
  createMusic,
  createSound,
  createSprite,
  createTransform,
  createBackground,
  createScroll,
  createParent,
  updateTexture,
  updatePosition,
  updateVelocity,
  updateHealth,
  updateDamage,
  updateHitbox,
  updateMusic,
  updateSound,
  updateSprite,
  updateTransform,
  updateBackground,
  updateScroll,
  updateParent,
  deleteTexture,
  deletePosition,
  deleteVelocity,
  deleteHealth,
  deleteDamage,
  deleteHitbox,
  deleteMusic,
  deleteSound,
  deleteSprite,
  deleteTransform,
  deleteBackground,
  deleteScroll,
  deleteParent,
};

enum class TexturePath : uint32_t {
  Player,
  Enemy,
  Bullet,
  Background,
};

enum class KeyAction : uint32_t {
  moveUp,
  moveDown,
  moveLeft,
  moveRight,
  shoot,
};

struct TextureComponent {
  TexturePath texturePath;
};

struct EntityId {
  size_t id;
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
  TexturePath texturePath;
  float x;
  float y;
};
