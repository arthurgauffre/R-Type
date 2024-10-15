/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkMessageFactory
*/

#pragma once

#include <NetworkMessage.hpp>
#include <NetworkMessagesCommunication.hpp>
#include <unordered_map>

class NetworkMessageFactory {
public:
  rtype::network::Message<NetworkMessages> createEntityMsg(size_t id) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createEntity;
    EntityId entity = {id};
    std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                     reinterpret_cast<uint8_t *>(&entity) +
                                         sizeof(EntityId));
    message.body.insert(message.body.end(), entityBytes.begin(),
                        entityBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }

  rtype::network::Message<NetworkMessages>
  createTextureMsg(std::string texturePath) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createTexture;
    TextureComponent texture = {texturePath};
    std::vector<uint8_t> textureBytes(reinterpret_cast<uint8_t *>(&texture),
                                      reinterpret_cast<uint8_t *>(&texture) +
                                          sizeof(TextureComponent));
    message.body.insert(message.body.end(), textureBytes.begin(),
                        textureBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createPositionMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createPosition;
    PositionComponent position = {x, y};
    std::vector<uint8_t> positionBytes(reinterpret_cast<uint8_t *>(&position),
                                       reinterpret_cast<uint8_t *>(&position) +
                                           sizeof(PositionComponent));
    message.body.insert(message.body.end(), positionBytes.begin(),
                        positionBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createVelocityMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createVelocity;
    VelocityComponent velocity = {x, y};
    std::vector<uint8_t> velocityBytes(reinterpret_cast<uint8_t *>(&velocity),
                                       reinterpret_cast<uint8_t *>(&velocity) +
                                           sizeof(VelocityComponent));
    message.body.insert(message.body.end(), velocityBytes.begin(),
                        velocityBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createHealthMsg(int health) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createHealth;
    HealthComponent healthComponent = {health};
    std::vector<uint8_t> healthBytes(
        reinterpret_cast<uint8_t *>(&healthComponent),
        reinterpret_cast<uint8_t *>(&healthComponent) +
            sizeof(HealthComponent));
    message.body.insert(message.body.end(), healthBytes.begin(),
                        healthBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createDamageMsg(int damage) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createDamage;
    DamageComponent damageComponent = {damage};
    std::vector<uint8_t> damageBytes(
        reinterpret_cast<uint8_t *>(&damageComponent),
        reinterpret_cast<uint8_t *>(&damageComponent) +
            sizeof(DamageComponent));
    message.body.insert(message.body.end(), damageBytes.begin(),
                        damageBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createHitboxMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createHitbox;
    HitboxComponent hitbox = {x, y};
    std::vector<uint8_t> hitboxBytes(reinterpret_cast<uint8_t *>(&hitbox),
                                     reinterpret_cast<uint8_t *>(&hitbox) +
                                         sizeof(HitboxComponent));
    message.body.insert(message.body.end(), hitboxBytes.begin(),
                        hitboxBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  createMusicMsg(std::string musicPath) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createMusic;
    MusicComponent music = {musicPath};
    std::vector<uint8_t> musicBytes(reinterpret_cast<uint8_t *>(&music),
                                    reinterpret_cast<uint8_t *>(&music) +
                                        sizeof(MusicComponent));
    message.body.insert(message.body.end(), musicBytes.begin(),
                        musicBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  createSoundMsg(std::string soundPath) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createSound;
    SoundComponent sound = {soundPath};
    std::vector<uint8_t> soundBytes(reinterpret_cast<uint8_t *>(&sound),
                                    reinterpret_cast<uint8_t *>(&sound) +
                                        sizeof(SoundComponent));
    message.body.insert(message.body.end(), soundBytes.begin(),
                        soundBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createSpriteMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createSprite;
    SpriteComponent sprite = {x, y};
    std::vector<uint8_t> spriteBytes(reinterpret_cast<uint8_t *>(&sprite),
                                     reinterpret_cast<uint8_t *>(&sprite) +
                                         sizeof(SpriteComponent));
    message.body.insert(message.body.end(), spriteBytes.begin(),
                        spriteBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  createTransformMsg(float x, float y, float scaleX, float scaleY) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createTransform;
    TransformComponent transform = {x, y, scaleX, scaleY};
    std::vector<uint8_t> transformBytes(
        reinterpret_cast<uint8_t *>(&transform),
        reinterpret_cast<uint8_t *>(&transform) + sizeof(TransformComponent));
    message.body.insert(message.body.end(), transformBytes.begin(),
                        transformBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  createBackgroundMsg(std::string texturePath, float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createBackground;
    BackgroundComponent background = {texturePath, x, y};
    std::vector<uint8_t> backgroundBytes(
        reinterpret_cast<uint8_t *>(&background),
        reinterpret_cast<uint8_t *>(&background) + sizeof(BackgroundComponent));
    message.body.insert(message.body.end(), backgroundBytes.begin(),
                        backgroundBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createScrollMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createScroll;
    ScrollComponent scroll = {x, y};
    std::vector<uint8_t> scrollBytes(reinterpret_cast<uint8_t *>(&scroll),
                                     reinterpret_cast<uint8_t *>(&scroll) +
                                         sizeof(ScrollComponent));
    message.body.insert(message.body.end(), scrollBytes.begin(),
                        scrollBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> createParentMsg(uint32_t parentID) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createParent;
    ParentComponent parent = {parentID};
    std::vector<uint8_t> parentBytes(reinterpret_cast<uint8_t *>(&parent),
                                     reinterpret_cast<uint8_t *>(&parent) +
                                         sizeof(ParentComponent));
    message.body.insert(message.body.end(), parentBytes.begin(),
                        parentBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  updateTextureMsg(std::string texturePath) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateTexture;
    TextureComponent texture = {texturePath};
    std::vector<uint8_t> textureBytes(reinterpret_cast<uint8_t *>(&texture),
                                      reinterpret_cast<uint8_t *>(&texture) +
                                          sizeof(TextureComponent));
    message.body.insert(message.body.end(), textureBytes.begin(),
                        textureBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updatePositionMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updatePosition;
    PositionComponent position = {x, y};
    std::vector<uint8_t> positionBytes(reinterpret_cast<uint8_t *>(&position),
                                       reinterpret_cast<uint8_t *>(&position) +
                                           sizeof(PositionComponent));
    message.body.insert(message.body.end(), positionBytes.begin(),
                        positionBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateVelocityMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateVelocity;
    VelocityComponent velocity = {x, y};
    std::vector<uint8_t> velocityBytes(reinterpret_cast<uint8_t *>(&velocity),
                                       reinterpret_cast<uint8_t *>(&velocity) +
                                           sizeof(VelocityComponent));
    message.body.insert(message.body.end(), velocityBytes.begin(),
                        velocityBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateHealthMsg(int health) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateHealth;
    HealthComponent healthComponent = {health};
    std::vector<uint8_t> healthBytes(
        reinterpret_cast<uint8_t *>(&healthComponent),
        reinterpret_cast<uint8_t *>(&healthComponent) +
            sizeof(HealthComponent));
    message.body.insert(message.body.end(), healthBytes.begin(),
                        healthBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateDamageMsg(int damage) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateDamage;
    DamageComponent damageComponent = {damage};
    std::vector<uint8_t> damageBytes(
        reinterpret_cast<uint8_t *>(&damageComponent),
        reinterpret_cast<uint8_t *>(&damageComponent) +
            sizeof(DamageComponent));
    message.body.insert(message.body.end(), damageBytes.begin(),
                        damageBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateHitboxMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateHitbox;
    HitboxComponent hitbox = {x, y};
    std::vector<uint8_t> hitboxBytes(reinterpret_cast<uint8_t *>(&hitbox),
                                     reinterpret_cast<uint8_t *>(&hitbox) +
                                         sizeof(HitboxComponent));
    message.body.insert(message.body.end(), hitboxBytes.begin(),
                        hitboxBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  updateMusicMsg(std::string musicPath) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateMusic;
    MusicComponent music = {musicPath};
    std::vector<uint8_t> musicBytes(reinterpret_cast<uint8_t *>(&music),
                                    reinterpret_cast<uint8_t *>(&music) +
                                        sizeof(MusicComponent));
    message.body.insert(message.body.end(), musicBytes.begin(),
                        musicBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  updateSoundMsg(std::string soundPath) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateSound;
    SoundComponent sound = {soundPath};
    std::vector<uint8_t> soundBytes(reinterpret_cast<uint8_t *>(&sound),
                                    reinterpret_cast<uint8_t *>(&sound) +
                                        sizeof(SoundComponent));
    message.body.insert(message.body.end(), soundBytes.begin(),
                        soundBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateSpriteMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateSprite;
    SpriteComponent sprite = {x, y};
    std::vector<uint8_t> spriteBytes(reinterpret_cast<uint8_t *>(&sprite),
                                     reinterpret_cast<uint8_t *>(&sprite) +
                                         sizeof(SpriteComponent));
    message.body.insert(message.body.end(), spriteBytes.begin(),
                        spriteBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  updateTransformMsg(float x, float y, float scaleX, float scaleY) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateTransform;
    TransformComponent transform = {x, y, scaleX, scaleY};
    std::vector<uint8_t> transformBytes(
        reinterpret_cast<uint8_t *>(&transform),
        reinterpret_cast<uint8_t *>(&transform) + sizeof(TransformComponent));
    message.body.insert(message.body.end(), transformBytes.begin(),
                        transformBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages>
  updateBackgroundMsg(std::string texturePath, float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateBackground;
    BackgroundComponent background = {texturePath, x, y};
    std::vector<uint8_t> backgroundBytes(
        reinterpret_cast<uint8_t *>(&background),
        reinterpret_cast<uint8_t *>(&background) + sizeof(BackgroundComponent));
    message.body.insert(message.body.end(), backgroundBytes.begin(),
                        backgroundBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateScrollMsg(float x, float y) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateScroll;
    ScrollComponent scroll = {x, y};
    std::vector<uint8_t> scrollBytes(reinterpret_cast<uint8_t *>(&scroll),
                                     reinterpret_cast<uint8_t *>(&scroll) +
                                         sizeof(ScrollComponent));
    message.body.insert(message.body.end(), scrollBytes.begin(),
                        scrollBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
  rtype::network::Message<NetworkMessages> updateParentMsg(uint32_t parentID) {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::updateParent;
    ParentComponent parent = {parentID};
    std::vector<uint8_t> parentBytes(reinterpret_cast<uint8_t *>(&parent),
                                     reinterpret_cast<uint8_t *>(&parent) +
                                         sizeof(ParentComponent));
    message.body.insert(message.body.end(), parentBytes.begin(),
                        parentBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    message << timeNow;
    return message;
  }
};
