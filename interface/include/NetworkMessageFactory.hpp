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
    rtype::network::Message<NetworkMessages> createEntityMsg(size_t id, Scene scene, int numClient)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createEntity;
        EntityStruct entity = {id, numClient};
        SceneStatus sceneStatus = {scene};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityStruct));
        std::vector<uint8_t> sceneBytes(reinterpret_cast<uint8_t *>(&sceneStatus),
                                        reinterpret_cast<uint8_t *>(&sceneStatus) +
                                            sizeof(SceneStatus));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), sceneBytes.begin(),
                            sceneBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateEntityMsg(size_t id, Scene scene, int numClient)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateEntity;
        EntityStruct entity = {id, numClient};
        SceneStatus sceneStatus = {scene};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityStruct));
        std::vector<uint8_t> sceneBytes(reinterpret_cast<uint8_t *>(&sceneStatus),
                                        reinterpret_cast<uint8_t *>(&sceneStatus) +
                                            sizeof(SceneStatus));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), sceneBytes.begin(),
                            sceneBytes.end());
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
    rtype::network::Message<NetworkMessages> createRectangleShapeMsg(
        size_t id, float x, float y, float width, float height, RColor color)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createRectangleShape;
        EntityId entity = {id};
        RectangleShapeComponent rectangleShape = {x, y, width, height, color};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> rectangleShapeBytes(
            reinterpret_cast<uint8_t *>(&rectangleShape),
            reinterpret_cast<uint8_t *>(&rectangleShape) +
                sizeof(RectangleShapeComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), rectangleShapeBytes.begin(),
                            rectangleShapeBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateRectangleShapeMsg(
        size_t id, float x, float y, float width, float height, RColor color)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateRectangleShape;
        EntityId entity = {id};
        RectangleShapeComponent rectangleShape = {x, y, width, height, color};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> rectangleShapeBytes(
            reinterpret_cast<uint8_t *>(&rectangleShape),
            reinterpret_cast<uint8_t *>(&rectangleShape) +
                sizeof(RectangleShapeComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), rectangleShapeBytes.begin(),
                            rectangleShapeBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createVelocityMsg(size_t id, float x,
                                                               float y, float actualX, float actualY)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createVelocity;
        EntityId entity = {id};
        VelocityComponent velocity = {x, y, actualX, actualY};
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
    createTransformMsg(size_t id, float x, float y, float scaleX, float scaleY, float rotation)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createTransform;
        EntityId entity = {id};
        TransformComponent transform = {x, y, scaleX, scaleY, rotation};
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

    rtype::network::Message<NetworkMessages> createInputMsg(size_t id, int numClient)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createInput;
        EntityId entity = {id};
        InputComponent input = {numClient};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> inputBytes(reinterpret_cast<uint8_t *>(&input),
                                            reinterpret_cast<uint8_t *>(&input) +
                                                sizeof(InputComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), inputBytes.begin(),
                            inputBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createTypeMsg(size_t id,
                                                          Type type)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createType;
        EntityId entity = {id};
        TypeComponent typeComponent = {type};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> typeBytes(reinterpret_cast<uint8_t *>(&typeComponent),
                                      reinterpret_cast<uint8_t *>(&typeComponent) +
                                          sizeof(TypeComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), typeBytes.begin(),
                            typeBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createCooldownMsg(size_t id,
                                                              float cooldown,
                                                              float timeRemaining)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createCooldown;
        EntityId entity = {id};
        CoolDownComponent cooldownComponent = {cooldown, timeRemaining};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> cooldownBytes(
            reinterpret_cast<uint8_t *>(&cooldownComponent),
            reinterpret_cast<uint8_t *>(&cooldownComponent) +
                sizeof(CoolDownComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), cooldownBytes.begin(),
                            cooldownBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateTypeMsg(size_t id,
                                                          Type type)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateType;
        EntityId entity = {id};
        TypeComponent typeComponent = {type};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> typeBytes(reinterpret_cast<uint8_t *>(&typeComponent),
                                      reinterpret_cast<uint8_t *>(&typeComponent) +
                                          sizeof(TypeComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), typeBytes.begin(),
                            typeBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateCooldownMsg(size_t id,
                                                              float cooldown,
                                                              float timeRemaining)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateCooldown;
        EntityId entity = {id};
        CoolDownComponent cooldownComponent = {cooldown, timeRemaining};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> cooldownBytes(
            reinterpret_cast<uint8_t *>(&cooldownComponent),
            reinterpret_cast<uint8_t *>(&cooldownComponent) +
                sizeof(CoolDownComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), cooldownBytes.begin(),
                            cooldownBytes.end());
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
                                                               float y, float actualX, float actualY)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateVelocity;
        EntityId entity = {id};
        VelocityComponent velocity = {x, y, actualX, actualY};
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
    updateTransformMsg(size_t id, float x, float y, float scaleX, float scaleY, float rotation)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateTransform;
        EntityId entity = {id};
        TransformComponent transform = {x, y, scaleX, scaleY, rotation};
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
    rtype::network::Message<NetworkMessages> deleteTypeMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteType;
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
    rtype::network::Message<NetworkMessages> deleteCooldownMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteCooldown;
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
    rtype::network::Message<NetworkMessages> createSizeMsg(size_t id, float x,
                                                          float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createSize;
        EntityId entity = {id};
        SizeComponent size = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> sizeBytes(reinterpret_cast<uint8_t *>(&size),
                                       reinterpret_cast<uint8_t *>(&size) +
                                           sizeof(SizeComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), sizeBytes.begin(),
                            sizeBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateSizeMsg(size_t id, float x,
                                                          float y)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateSize;
        EntityId entity = {id};
        SizeComponent size = {x, y};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> sizeBytes(reinterpret_cast<uint8_t *>(&size),
                                       reinterpret_cast<uint8_t *>(&size) +
                                           sizeof(SizeComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), sizeBytes.begin(),
                            sizeBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> deleteSizeMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteSize;
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
    rtype::network::Message<NetworkMessages> createAIMsg(size_t id, AIType type)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createAI;
        EntityId entity = {id};
        AIComponent ai = {type};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> aiBytes(reinterpret_cast<uint8_t *>(&ai),
                                    reinterpret_cast<uint8_t *>(&ai) +
                                        sizeof(AIComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), aiBytes.begin(),
                            aiBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateAIMsg(size_t id, AIType type)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateAI;
        EntityId entity = {id};
        AIComponent ai = {type};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        std::vector<uint8_t> aiBytes(reinterpret_cast<uint8_t *>(&ai),
                                    reinterpret_cast<uint8_t *>(&ai) +
                                        sizeof(AIComponent));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), aiBytes.begin(),
                            aiBytes.end());
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> deleteAIMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteAI;
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
    rtype::network::Message<NetworkMessages> createMenuMsg()
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::menu;
        std::cout << "create menu" << std::endl;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createGameMsg()
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::game;
        std::cout << "create game" << std::endl;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createKeyBindMsg()
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::keyBind;
        std::cout << "create keyBind" << std::endl;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> deleteRectangleShapeMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteRectangleShape;
        EntityId entity = {id};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) +
                                             sizeof(EntityId));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createOnClickMsg(size_t id, int numClient, Action action)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createOnClick;
        EntityId entity = {id};
        OnClickComponent onClick = {action, numClient};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> onClickBytes(reinterpret_cast<uint8_t *>(&onClick),
                                          reinterpret_cast<uint8_t *>(&onClick) + sizeof(OnClickComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), onClickBytes.begin(), onClickBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateOnClickMsg(size_t id, Action action)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateOnClick;
        EntityId entity = {id};
        ActionMsg onClick = {action};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> onClickBytes(reinterpret_cast<uint8_t *>(&onClick),
                                          reinterpret_cast<uint8_t *>(&onClick) + sizeof(ActionMsg));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), onClickBytes.begin(), onClickBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> deleteOnClickMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteOnClick;
        EntityId entity = {id};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> createTextMsg(size_t id, float x, float y, TextFont font, TextString string, int size, RColor color)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createText;
        EntityId entity = {id};
        TextComponent text = {x, y, font, string, size, color};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> textBytes(reinterpret_cast<uint8_t *>(&text),
                                       reinterpret_cast<uint8_t *>(&text) + sizeof(TextComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), textBytes.begin(), textBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> updateTextMsg(size_t id, float x, float y, TextFont font, TextString string, int size, RColor color)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateText;
        EntityId entity = {id};
        TextComponent text = {x, y, font, string, size, color};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> textBytes(reinterpret_cast<uint8_t *>(&text),
                                       reinterpret_cast<uint8_t *>(&text) + sizeof(TextComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), textBytes.begin(), textBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
    rtype::network::Message<NetworkMessages> deleteTextMsg(size_t id)
    {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteText;
        EntityId entity = {id};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
};
