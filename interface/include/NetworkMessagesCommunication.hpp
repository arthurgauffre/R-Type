/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkMessages
*/

#pragma once

#include <cstdint>
#include <graphics/Color.hpp>
#include <r-type/Enum.hpp>

enum class NetworkMessages : uint32_t {
  ServerAcceptance,
  ServerDenial,
  ServerPing,
  MessageAll,
  ServerMessage,
  ClientConnection,
  ClientDisconnection,
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
  createParent,
  createInput,
  createCooldown,
  createType,
  createSize,
  createAI,
  createRectangleShape,
  createOnCLick,
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
  updateParent,
  updateInput,
  updateType,
  updateSize,
  updateCooldown,
  updateAI,
  updateRectangleShape,
  updateOnClick,
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
  deleteParent,
  deleteInput,
  deleteCooldown,
  deleteType,
  deleteSize,
  deleteAI,
  deleteRectangleShape,
  deleteOnClick,
  acknowledgementMesage,
  menu,
  action,
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

enum class AIType : uint32_t {
  Linear,
  Sinusoidal,
  Circular,
  Unknown,
};

enum class TexturePath : uint32_t {
  Player,
  Enemy,
  Bullet,
  Background,
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

struct OnClickComponent {
  Action action;
  int numClient;
};

struct EntityStruct {
  size_t id;
  int numClient;
};

struct EntityId {
  size_t id;
};

struct SceneStatus {
  Scene scene;
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

struct CoolDownComponent {
  float cooldown;
  float timeRemaining;
};

struct TypeComponent {
  EntityType type;
};

struct SizeComponent {
  float x;
  float y;
};

struct AIComponent {
  AIType type;
  float elapsedTime;
};

struct InputComponent {
  int numClient;
};

struct RectangleShapeComponent {
  float x;
  float y;
  float width;
  float height;
  RColor color;
};

struct BindKey {
  KeyBoard key;
  Action action;
};

struct ActionMsg {
  Action action;
};
