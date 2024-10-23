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

class NetworkMessageFactory
{
public:
    rtype::network::Message<NetworkMessages> createEntityMsg(size_t id)
    {
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
    rtype::network::Message<NetworkMessages> updateEntityMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteEntity;
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
    createTextureMsg(size_t id, TexturePath texturePath)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createTexture;
        EntityId entity = {id};
        TextureComponent texture = {texturePath};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> textureBytes(reinterpret_cast<uint8_t *>(&texture),
                                          reinterpret_cast<uint8_t *>(&texture) +
                                              sizeof(TextureComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), textureBytes.begin(),
                            textureBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createVelocityMsg(size_t id, float x,
                                                               float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createVelocity;
        EntityId entity = {id};
        VelocityComponent velocity = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> velocityBytes(reinterpret_cast<uint8_t *>(&velocity),
                                           reinterpret_cast<uint8_t *>(&velocity) +
                                               sizeof(VelocityComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), velocityBytes.begin(),
                            velocityBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createHealthMsg(size_t id,
                                                             int health)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createHealth;
        EntityId entity = {id};
        HealthComponent healthComponent = {health};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> healthBytes(
            reinterpret_cast<uint8_t *>(&healthComponent),
            reinterpret_cast<uint8_t *>(&healthComponent) +
                sizeof(HealthComponent));
        message.body.insert(message.body.end(), healthBytes.begin(),
                            healthBytes.end());
        message.body.insert(message.body.end(), healthBytes.begin(),
                            healthBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createDamageMsg(size_t id,
                                                             int damage)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createDamage;
        EntityId entity = {id};
        DamageComponent damageComponent = {damage};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> damageBytes(
            reinterpret_cast<uint8_t *>(&damageComponent),
            reinterpret_cast<uint8_t *>(&damageComponent) +
                sizeof(DamageComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), damageBytes.begin(),
                            damageBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createHitboxMsg(size_t id, float x,
                                                             float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createHitbox;
        EntityId entity = {id};
        HitboxComponent hitbox = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> hitboxBytes(reinterpret_cast<uint8_t *>(&hitbox),
                                         reinterpret_cast<uint8_t *>(&hitbox) +
                                             sizeof(HitboxComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), hitboxBytes.begin(),
                            hitboxBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    //   rtype::network::Message<NetworkMessages>
    //   createMusicMsg(size_t id, std::string musicPath) {
    //     rtype::network::Message<NetworkMessages> message;
    //     message.header.id = NetworkMessages::createMusic;
    //     EntityId entity = {id};
    //     MusicComponent music = {musicPath};
    //     std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
    //                                      reinterpret_cast<uint8_t *>(&entity) +
    //                                          sizeof(EntityId));
    //     std::vector<uint8_t> musicBytes(reinterpret_cast<uint8_t *>(&music),
    //                                     reinterpret_cast<uint8_t *>(&music) +
    //                                         sizeof(MusicComponent));
    //     message.body.insert(message.body.end(), entityBytes.begin(),
    //                         entityBytes.end());
    //     message.body.insert(message.body.end(), musicBytes.begin(),
    //                         musicBytes.end());
    //     std::chrono::system_clock::time_point timeNow =
    //         std::chrono::system_clock::now();
    //     message << timeNow;
    //     return message;
    //   }
    //   rtype::network::Message<NetworkMessages>
    //   createSoundMsg(size_t id, std::string soundPath) {
    //     rtype::network::Message<NetworkMessages> message;
    //     message.header.id = NetworkMessages::createSound;
    //     EntityId entity = {id};
    //     SoundComponent sound = {soundPath};
    //     std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
    //                                      reinterpret_cast<uint8_t *>(&entity) +
    //                                          sizeof(EntityId));
    //     std::vector<uint8_t> soundBytes(reinterpret_cast<uint8_t *>(&sound),
    //                                     reinterpret_cast<uint8_t *>(&sound) +
    //                                         sizeof(SoundComponent));
    //     message.body.insert(message.body.end(), entityBytes.begin(),
    //                         entityBytes.end());
    //     message.body.insert(message.body.end(), soundBytes.begin(),
    //                         soundBytes.end());
    //     std::chrono::system_clock::time_point timeNow =
    //         std::chrono::system_clock::now();
    //     message << timeNow;
    //     return message;
    //   }
    rtype::network::Message<NetworkMessages> createSpriteMsg(size_t id, float x,
                                                             float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createSprite;
        EntityId entity = {id};
        SpriteComponent sprite = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> spriteBytes(reinterpret_cast<uint8_t *>(&sprite),
                                         reinterpret_cast<uint8_t *>(&sprite) +
                                             sizeof(SpriteComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), spriteBytes.begin(),
                            spriteBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages>
    createTransformMsg(size_t id, float x, float y, float scaleX, float scaleY)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createTransform;
        EntityId entity = {id};
        TransformComponent transform = {x, y, scaleX, scaleY};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> transformBytes(
            reinterpret_cast<uint8_t *>(&transform),
            reinterpret_cast<uint8_t *>(&transform) + sizeof(TransformComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), transformBytes.begin(),
                            transformBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages>
    createBackgroundMsg(size_t id, TexturePath texturePath, float x, float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createBackground;
        EntityId entity = {id};
        BackgroundComponent background = {texturePath, x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> backgroundBytes(
            reinterpret_cast<uint8_t *>(&background),
            reinterpret_cast<uint8_t *>(&background) + sizeof(BackgroundComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), backgroundBytes.begin(),
                            backgroundBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createParentMsg(size_t id,
                                                             uint32_t parentID)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createParent;
        EntityId entity = {id};
        ParentComponent parent = {parentID};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> parentBytes(reinterpret_cast<uint8_t *>(&parent),
                                         reinterpret_cast<uint8_t *>(&parent) +
                                             sizeof(ParentComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), parentBytes.begin(),
                            parentBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    rtype::network::Message<NetworkMessages> createInputMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createInput;
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
    updateTextureMsg(size_t id, TexturePath texturePath)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateTexture;
        EntityId entity = {id};
        TextureComponent texture = {texturePath};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> textureBytes(reinterpret_cast<uint8_t *>(&texture),
                                          reinterpret_cast<uint8_t *>(&texture) +
                                              sizeof(TextureComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), textureBytes.begin(),
                            textureBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateVelocityMsg(size_t id, float x,
                                                               float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateVelocity;
        EntityId entity = {id};
        VelocityComponent velocity = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> velocityBytes(reinterpret_cast<uint8_t *>(&velocity),
                                           reinterpret_cast<uint8_t *>(&velocity) +
                                               sizeof(VelocityComponent));
        message.body.insert(message.body.end(), velocityBytes.begin(),
                            velocityBytes.end());
        message.body.insert(message.body.end(), velocityBytes.begin(),
                            velocityBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateHealthMsg(size_t id,
                                                             int health)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateHealth;
        EntityId entity = {id};
        HealthComponent healthComponent = {health};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> healthBytes(
            reinterpret_cast<uint8_t *>(&healthComponent),
            reinterpret_cast<uint8_t *>(&healthComponent) +
                sizeof(HealthComponent));
        message.body.insert(message.body.end(), healthBytes.begin(),
                            healthBytes.end());
        message.body.insert(message.body.end(), healthBytes.begin(),
                            healthBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateDamageMsg(size_t id,
                                                             int damage)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateDamage;
        EntityId entity = {id};
        DamageComponent damageComponent = {damage};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> damageBytes(
            reinterpret_cast<uint8_t *>(&damageComponent),
            reinterpret_cast<uint8_t *>(&damageComponent) +
                sizeof(DamageComponent));
        message.body.insert(message.body.end(), damageBytes.begin(),
                            damageBytes.end());
        message.body.insert(message.body.end(), damageBytes.begin(),
                            damageBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateHitboxMsg(size_t id, float x,
                                                             float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateHitbox;
        EntityId entity = {id};
        HitboxComponent hitbox = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> hitboxBytes(reinterpret_cast<uint8_t *>(&hitbox),
                                         reinterpret_cast<uint8_t *>(&hitbox) +
                                             sizeof(HitboxComponent));
        message.body.insert(message.body.end(), hitboxBytes.begin(),
                            hitboxBytes.end());
        message.body.insert(message.body.end(), hitboxBytes.begin(),
                            hitboxBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    //   rtype::network::Message<NetworkMessages>
    //   updateMusicMsg(size_t id, std::string musicPath) {
    //     rtype::network::Message<NetworkMessages> message;
    //     message.header.id = NetworkMessages::updateMusic;
    //     EntityId entity = {id};
    //     MusicComponent music = {musicPath};
    //     std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
    //                                      reinterpret_cast<uint8_t *>(&entity) +
    //                                          sizeof(EntityId));
    //     std::vector<uint8_t> musicBytes(reinterpret_cast<uint8_t *>(&music),
    //                                     reinterpret_cast<uint8_t *>(&music) +
    //                                         sizeof(MusicComponent));
    //     message.body.insert(message.body.end(), musicBytes.begin(),
    //                         musicBytes.end());
    //     message.body.insert(message.body.end(), musicBytes.begin(),
    //                         musicBytes.end());
    //     std::chrono::system_clock::time_point timeNow =
    //         std::chrono::system_clock::now();
    //     message << timeNow;
    //     return message;
    //   }
    //   rtype::network::Message<NetworkMessages>
    //   updateSoundMsg(std::string soundPath) {
    //     rtype::network::Message<NetworkMessages> message;
    //     message.header.id = NetworkMessages::updateSound;
    //     EntityId entity = {0};
    //     SoundComponent sound = {soundPath};
    //     std::vector<uint8_t> EntityBytes(reinterpret_cast<uint8_t *>(&entity),
    //                                     reinterpret_cast<uint8_t *>(&entity) +
    //                                         sizeof(EntityId));
    //     std::vector<uint8_t> soundBytes(reinterpret_cast<uint8_t *>(&sound),
    //                                     reinterpret_cast<uint8_t *>(&sound) +
    //                                         sizeof(SoundComponent));
    //     message.body.insert(message.body.end(), EntityBytes.begin(),
    //                         EntityBytes.end());
    //     message.body.insert(message.body.end(), soundBytes.begin(),
    //                         soundBytes.end());
    //     std::chrono::system_clock::time_point timeNow =
    //         std::chrono::system_clock::now();
    //     message << timeNow;
    //     return message;
    //   }
    rtype::network::Message<NetworkMessages> updateSpriteMsg(size_t id, float x,
                                                             float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateSprite;
        EntityId entity = {id};
        SpriteComponent sprite = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> spriteBytes(reinterpret_cast<uint8_t *>(&sprite),
                                         reinterpret_cast<uint8_t *>(&sprite) +
                                             sizeof(SpriteComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), spriteBytes.begin(),
                            spriteBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages>
    updateTransformMsg(size_t id, float x, float y, float scaleX, float scaleY)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateTransform;
        EntityId entity = {id};
        TransformComponent transform = {x, y, scaleX, scaleY};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> transformBytes(
            reinterpret_cast<uint8_t *>(&transform),
            reinterpret_cast<uint8_t *>(&transform) + sizeof(TransformComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), transformBytes.begin(),
                            transformBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages>
    updateBackgroundMsg(size_t id, TexturePath texturePath, float x, float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateBackground;
        EntityId entity = {id};
        BackgroundComponent background = {texturePath, x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
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
    rtype::network::Message<NetworkMessages> updateParentMsg(size_t id,
                                                             uint32_t parentID)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateParent;
        EntityId entity = {id};
        ParentComponent parent = {parentID};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> parentBytes(reinterpret_cast<uint8_t *>(&parent),
                                         reinterpret_cast<uint8_t *>(&parent) +
                                             sizeof(ParentComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), parentBytes.begin(),
                            parentBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    rtype::network::Message<NetworkMessages> updateInputMsg(size_t id,
                                                            BindKey bind)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateInput;
        EntityId entity = {id};
        BindKey bindInput = {bind};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> inputBytes(reinterpret_cast<uint8_t *>(&bindInput),
                                        reinterpret_cast<uint8_t *>(&bindInput) +
                                            sizeof(bindInput));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), inputBytes.begin(),
                            inputBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    rtype::network::Message<NetworkMessages> deleteEntityMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteEntity;
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
    rtype::network::Message<NetworkMessages> deleteTextureMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteTexture;
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
    rtype::network::Message<NetworkMessages> deletePositionMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deletePosition;
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
    rtype::network::Message<NetworkMessages> deleteVelocityMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteVelocity;
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
    rtype::network::Message<NetworkMessages> deleteHealthMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteHealth;
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
    rtype::network::Message<NetworkMessages> deleteDamageMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteDamage;
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
    rtype::network::Message<NetworkMessages> deleteHitboxMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteHitbox;
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
    rtype::network::Message<NetworkMessages> deleteMusicMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteMusic;
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
    rtype::network::Message<NetworkMessages> deleteSoundMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteSound;
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
    rtype::network::Message<NetworkMessages> deleteSpriteMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteSprite;
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
    rtype::network::Message<NetworkMessages> deleteTransformMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteTransform;
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
    rtype::network::Message<NetworkMessages> deleteBackgroundMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteBackground;
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
    rtype::network::Message<NetworkMessages> deleteParentMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteParent;
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

    rtype::network::Message<NetworkMessages> deleteInputMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteInput;
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
};
