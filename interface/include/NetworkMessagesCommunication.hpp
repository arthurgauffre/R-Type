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
  createParent,
  createInput,
  createCooldown,
  createType,
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
  updateParent,
  updateInput,
  updateType,
  updateCooldown,
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
  deleteParent,
  deleteInput,
  deleteCooldown,
  deleteType,
  moveUp,
  moveDown,
  moveLeft,
  moveRight,
  shoot,
  none,
};

enum class EntityType : uint32_t {
  Player,
  Enemy,
  Weapon,
  Projectile,
  Player_projectile,
  Enemy_projectile,
  Background,
  Unknown,
};

enum class TexturePath : uint32_t {
  Player,
  Enemy,
  Bullet,
  Background,
};

enum class BindAction : uint32_t {
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Shoot,
};

enum class KeyBoard : uint32_t {
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
};

struct TextureComponent {
  TexturePath texturePath;
};

struct EntityId {
  size_t id;
};

struct VelocityComponent {
  float x;
  float y;
  float actualX;
  float actualY;
};

struct ParentComponent {
  uint32_t parentID;
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
  float rotation;
};

struct BackgroundComponent {
  TexturePath texturePath;
  float x;
  float y;
};

struct CoolDownComponent {
  float cooldown;
  float timeRemaining;
};

struct TypeComponent {
  EntityType type;
};

struct BindKey {
  KeyBoard key;
  BindAction action;
};