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
  createOnClick,
  createText,
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
  updateText,
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
  deleteText,
  acknowledgementMesageToCreateEntity,
  acknowledgementMesageToCreateInput,
  acknowledgementMesageToCreateRectangleShape,
  acknowledgementMesageToCreateOnClick,
  acknowledgementMesageToCreateText,
  menu,
  game,
  keyBind,
  action,
  none,
};

struct TextureComponent {
  TexturePath texturePath;
};

struct TextComponent {
  float x;
  float y;
  TextFont textFont;
  TextString textString;
  int size;
  RColor color;
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

struct soundComponent {
  SoundPath soundPath;
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

struct SoundComponent {
  SoundPath soundPath;
  bool play;
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
  Type type;
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
