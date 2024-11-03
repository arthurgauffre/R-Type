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
    /**
     * @brief Creates a network message for creating an entity.
     *
     * This function constructs a network message that contains information
     * about an entity to be created, including its ID, the scene it belongs to,
     * and the client number. The message also includes a timestamp of when it
     * was created.
     *
     * @param id The unique identifier of the entity.
     * @param scene The scene to which the entity belongs.
     * @param numClient The client number associated with the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> createEntityMsg(size_t id, Scene scene, int numClient)
    {
        // std::cout << "Creating entity message" << std::endl;
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

    /**
     * @brief Creates a network message to update an entity.
     *
     * This function constructs a network message that contains information about an entity update.
     * It includes the entity ID, the client number, the scene status, and the current timestamp.
     *
     * @param id The ID of the entity to be updated.
     * @param scene The current scene status.
     * @param numClient The client number associated with the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the entity update information.
     */
    rtype::network::Message<NetworkMessages> updateEntityMsg(size_t id, Scene scene, int numClient)
    {
        // std::cout << "Updating entity message" << std::endl;
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

    /**
     * @brief Creates a network message for creating a texture.
     *
     * This function constructs a network message that contains information
     * about a texture to be created. The message includes the entity ID and
     * the texture path, and appends the current system time to the message body.
     *
     * @param id The ID of the entity for which the texture is being created.
     * @param texturePath The path to the texture file.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages>
    createTextureMsg(size_t id, TexturePath texturePath)
    {
        // std::cout << "Creating texture message" << std::endl;
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

    /**
     * @brief Creates a network message for a rectangle shape.
     *
     * This function constructs a network message that contains information about
     * a rectangle shape, including its ID, position, dimensions, and color.
     *
     * @param id The unique identifier for the rectangle shape entity.
     * @param x The x-coordinate of the rectangle shape.
     * @param y The y-coordinate of the rectangle shape.
     * @param width The width of the rectangle shape.
     * @param height The height of the rectangle shape.
     * @param color The color of the rectangle shape.
     * @return A network message containing the rectangle shape information.
     */
    rtype::network::Message<NetworkMessages> createRectangleShapeMsg(
        size_t id, float x, float y, float width, float height, RColor color)
    {
        // std::cout << "Creating rectangle shape message" << std::endl;
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

    /**
     * @brief Creates a network message to update a rectangle shape.
     *
     * This function constructs a network message that contains information about
     * updating a rectangle shape. The message includes the entity ID, the rectangle
     * shape's position, dimensions, and color, as well as the current timestamp.
     *
     * @param id The unique identifier of the entity.
     * @param x The x-coordinate of the rectangle shape.
     * @param y The y-coordinate of the rectangle shape.
     * @param width The width of the rectangle shape.
     * @param height The height of the rectangle shape.
     * @param color The color of the rectangle shape.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateRectangleShapeMsg(
        size_t id, float x, float y, float width, float height, RColor color)
    {
        // std::cout << "Updating rectangle shape message" << std::endl;
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

    /**
     * @brief Creates a velocity message for the network.
     *
     * This function constructs a network message containing velocity information
     * for a specific entity. The message includes the entity ID and its velocity
     * components (x, y, actualX, actualY), and appends the current system time.
     *
     * @param id The unique identifier of the entity.
     * @param x The x component of the velocity.
     * @param y The y component of the velocity.
     * @param actualX The actual x position of the entity.
     * @param actualY The actual y position of the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed velocity message.
     */
    rtype::network::Message<NetworkMessages> createVelocityMsg(size_t id, float x,
                                                               float y, float actualX, float actualY)
    {
        // std::cout << "Creating velocity message" << std::endl;
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

    /**
     * @brief Creates a health message for a network entity.
     *
     * This function constructs a network message that contains the health information
     * of an entity identified by the given ID. The message is serialized into a byte
     * vector and includes a timestamp of when the message was created.
     *
     * @param id The unique identifier of the entity.
     * @param health The health value of the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed health message.
     */
    rtype::network::Message<NetworkMessages> createHealthMsg(size_t id,
                                                             int health)
    {
        // std::cout << "Creating health message" << std::endl;
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

    /**
     * @brief Creates a damage message for the network.
     *
     * This function constructs a network message that contains information about
     * an entity taking damage. The message includes the entity ID, the damage
     * amount, and a timestamp of when the message was created.
     *
     * @param id The ID of the entity that took damage.
     * @param damage The amount of damage the entity took.
     * @return rtype::network::Message<NetworkMessages> The constructed damage message.
     */
    rtype::network::Message<NetworkMessages> createDamageMsg(size_t id,
                                                             int damage)
    {
        // std::cout << "Creating damage message" << std::endl;
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

    /**
     * @brief Creates a network message for a hitbox.
     *
     * This function constructs a network message that contains information about
     * a hitbox, including the entity ID and the hitbox coordinates (x, y). The
     * message is serialized into a byte vector and includes a timestamp.
     *
     * @param id The ID of the entity.
     * @param x The x-coordinate of the hitbox.
     * @param y The y-coordinate of the hitbox.
     * @return A network message containing the hitbox information.
     */
    rtype::network::Message<NetworkMessages> createHitboxMsg(size_t id, float x,
                                                             float y)
    {
        // std::cout << "Creating hitbox message" << std::endl;
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

    /**
     * @brief Creates a network message for a sprite.
     *
     * This function constructs a network message that contains information about a sprite,
     * including its ID, position (x, y), and color. The message is then timestamped with the
     * current system time.
     *
     * @param id The unique identifier for the sprite entity.
     * @param x The x-coordinate of the sprite's position.
     * @param y The y-coordinate of the sprite's position.
     * @param color The color of the sprite.
     * @return A network message containing the sprite information and a timestamp.
     */
    rtype::network::Message<NetworkMessages> createSpriteMsg(size_t id, float x,
                                                             float y, RColor color)
    {
        // std::cout << "Creating sprite message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createSprite;
        EntityId entity = {id};
        SpriteComponent sprite = {x, y, color};
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

    /**
     * @brief Creates a network message containing transform information.
     *
     * This function creates a network message that includes the transform
     * information of an entity. The message contains the entity ID and its
     * transform components such as position, scale, and rotation.
     *
     * @param id The unique identifier of the entity.
     * @param x The x-coordinate of the entity's position.
     * @param y The y-coordinate of the entity's position.
     * @param scaleX The scale factor along the x-axis.
     * @param scaleY The scale factor along the y-axis.
     * @param rotation The rotation angle of the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the transform information.
     */
    rtype::network::Message<NetworkMessages>
    createTransformMsg(size_t id, float x, float y, float scaleX, float scaleY, float rotation)
    {
        // std::cout << "Creating transform message" << std::endl;
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

    /**
     * @brief Creates a network message to represent a parent entity.
     *
     * This function constructs a network message with the specified entity ID and parent ID.
     * It serializes the entity ID and parent ID into the message body and appends the current
     * system time to the message.
     *
     * @param id The ID of the entity.
     * @param parentID The ID of the parent entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> createParentMsg(size_t id,
                                                             uint32_t parentID)
    {
        // std::cout << "Creating parent message" << std::endl;
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

    /**
     * @brief Creates an input message for the network.
     *
     * This function constructs a network message containing input data for a specific entity.
     * The message includes the entity ID, input component, and the current timestamp.
     *
     * @param id The ID of the entity.
     * @param numClient The client number associated with the input.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> createInputMsg(size_t id, int numClient)
    {
        // std::cout << "Creating input message" << std::endl;
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

    /**
     * @brief Creates a network message of type `createType`.
     *
     * This function constructs a network message with the specified entity ID and type component.
     * The message header is set to `NetworkMessages::createType`, and the body contains the serialized
     * entity ID and type component. Additionally, the current system time is appended to the message body.
     *
     * @param id The ID of the entity.
     * @param type The type component of the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> createTypeMsg(size_t id,
                                                          Type type)
    {
        // std::cout << "Creating type message" << std::endl;
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

    /**
     * @brief Creates a cooldown message for the network.
     *
     * This function constructs a network message that contains information about
     * an entity's cooldown status. The message includes the entity ID, the cooldown
     * duration, the remaining time for the cooldown, and the current system time.
     *
     * @param id The unique identifier of the entity.
     * @param cooldown The total cooldown duration.
     * @param timeRemaining The remaining time for the cooldown.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> createCooldownMsg(size_t id,
                                                              float cooldown,
                                                              float timeRemaining)
    {
        // std::cout << "Creating cooldown message" << std::endl;
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

    /**
     * @brief Creates a network message to update the type of an entity.
     *
     * This function constructs a network message with the specified entity ID and type.
     * The message includes the entity ID, type component, and the current timestamp.
     *
     * @param id The ID of the entity to update.
     * @param type The new type to assign to the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateTypeMsg(size_t id,
                                                          Type type)
    {
        // std::cout << "Updating type message" << std::endl;
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

    /**
     * @brief Creates a network message to update the cooldown of an entity.
     *
     * This function constructs a network message that contains information about
     * an entity's cooldown status. The message includes the entity ID, the cooldown
     * duration, and the remaining time for the cooldown.
     *
     * @param id The unique identifier of the entity.
     * @param cooldown The cooldown duration for the entity.
     * @param timeRemaining The remaining time for the cooldown.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateCooldownMsg(size_t id,
                                                              float cooldown,
                                                              float timeRemaining)
    {
        // std::cout << "Updating cooldown message" << std::endl;
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

    /**
     * @brief Creates a network message to update a texture.
     *
     * This function constructs a network message with the specified entity ID and texture path.
     * The message is used to update the texture of an entity in the network.
     *
     * @param id The ID of the entity whose texture is to be updated.
     * @param texturePath The path to the new texture.
     * @return A network message containing the entity ID and the new texture path.
     */
    rtype::network::Message<NetworkMessages>
    updateTextureMsg(size_t id, TexturePath texturePath)
    {
        // std::cout << "Updating texture message" << std::endl;
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

    /**
     * @brief Creates a network message to update the velocity of an entity.
     *
     * This function constructs a network message that contains the updated velocity
     * information for a specific entity. The message includes the entity ID and the
     * new velocity components (x, y) along with the actual position (actualX, actualY).
     * The message is timestamped with the current system time.
     *
     * @param id The unique identifier of the entity.
     * @param x The new velocity component along the x-axis.
     * @param y The new velocity component along the y-axis.
     * @param actualX The actual position of the entity along the x-axis.
     * @param actualY The actual position of the entity along the y-axis.
     * @return rtype::network::Message<NetworkMessages> The constructed network message
     *         containing the updated velocity information.
     */
    rtype::network::Message<NetworkMessages> updateVelocityMsg(size_t id, float x,
                                                               float y, float actualX, float actualY)
    {
        // std::cout << "Updating velocity message" << std::endl;
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

    /**
     * @brief Creates a network message to update the health of an entity.
     *
     * This function constructs a network message that contains the updated health
     * information for a specific entity. The message includes the entity ID and
     * the new health value, and it is timestamped with the current system time.
     *
     * @param id The ID of the entity whose health is being updated.
     * @param health The new health value for the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message
     *         containing the updated health information.
     */
    rtype::network::Message<NetworkMessages> updateHealthMsg(size_t id,
                                                             int health)
    {
        // std::cout << "Updating health message" << std::endl;
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

    /**
     * @brief Creates a network message to update the damage of an entity.
     *
     * This function constructs a network message that contains the updated damage
     * information for a specific entity. The message includes the entity ID and
     * the new damage value, and it is timestamped with the current system time.
     *
     * @param id The ID of the entity whose damage is being updated.
     * @param damage The new damage value to be assigned to the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message
     *         containing the update damage information.
     */
    rtype::network::Message<NetworkMessages> updateDamageMsg(size_t id,
                                                             int damage)
    {
        // std::cout << "Updating damage message" << std::endl;
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

    /**
     * @brief Creates a network message to update the hitbox of an entity.
     *
     * This function constructs a network message that contains the updated hitbox
     * information for a specific entity. The message includes the entity ID and
     * the new hitbox coordinates (x, y). The current system time is also appended
     * to the message.
     *
     * @param id The ID of the entity whose hitbox is being updated.
     * @param x The new x-coordinate of the hitbox.
     * @param y The new y-coordinate of the hitbox.
     * @return rtype::network::Message<NetworkMessages> The constructed network message
     *         containing the updated hitbox information.
     */
    rtype::network::Message<NetworkMessages> updateHitboxMsg(size_t id, float x,
                                                             float y)
    {
        // std::cout << "Updating hitbox message" << std::endl;
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

    /**
     * @brief Creates a network message to update a sprite's position and color.
     *
     * This function constructs a network message containing the entity ID, sprite
     * position (x, y), and color. The message is then timestamped with the current
     * system time.
     *
     * @param id The unique identifier of the entity.
     * @param x The x-coordinate of the sprite's position.
     * @param y The y-coordinate of the sprite's position.
     * @param color The color of the sprite.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateSpriteMsg(size_t id, float x,
                                                             float y, RColor color)
    {
        // std::cout << "Updating sprite message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateSprite;
        EntityId entity = {id};
        SpriteComponent sprite = {x, y, color};
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

    /**
     * @brief Creates a network message to update the transform of an entity.
     *
     * @param id The unique identifier of the entity.
     * @param x The x-coordinate of the entity's position.
     * @param y The y-coordinate of the entity's position.
     * @param scaleX The scale factor in the x direction.
     * @param scaleY The scale factor in the y direction.
     * @param rotation The rotation angle of the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the entity's transform update.
     */
    rtype::network::Message<NetworkMessages>
    updateTransformMsg(size_t id, float x, float y, float scaleX, float scaleY, float rotation)
    {
        // std::cout << "Updating transform message" << std::endl;
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

    /**
     * @brief Creates a network message to update the parent component of an entity.
     *
     * This function constructs a network message that contains the entity ID and
     * the new parent component ID. The message is then timestamped with the current
     * system time.
     *
     * @param id The ID of the entity whose parent component is being updated.
     * @param parentID The ID of the new parent component.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateParentMsg(size_t id,
                                                             uint32_t parentID)
    {
        // std::cout << "Updating parent message" << std::endl;
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

    /**
     * @brief Creates a network message to update input.
     *
     * This function constructs a network message of type `updateInput` with the
     * provided entity ID and bind key. The message body includes the serialized
     * entity ID and bind key, followed by the current system time.
     *
     * @param id The ID of the entity to update.
     * @param bind The key binding to update.
     * @return A `rtype::network::Message<NetworkMessages>` object containing the
     *         update input message.
     */
    rtype::network::Message<NetworkMessages> updateInputMsg(size_t id,
                                                            BindKey bind)
    {
        // std::cout << "Updating input message" << std::endl;
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

    /**
     * @brief Creates a network message to delete an entity.
     *
     * This function constructs a network message that indicates an entity should be deleted.
     * The message includes the entity ID and the current timestamp.
     *
     * @param id The ID of the entity to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed delete entity message.
     */
    rtype::network::Message<NetworkMessages> deleteEntityMsg(size_t id)
    {
        // std::cout << "Deleting entity message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a texture.
     *
     * This function constructs a network message with the specified texture ID
     * to indicate that the texture should be deleted. The message includes the
     * texture ID and the current system time.
     *
     * @param id The ID of the texture to be deleted.
     * @return A network message containing the delete texture command.
     */
    rtype::network::Message<NetworkMessages> deleteTextureMsg(size_t id)
    {
        // std::cout << "Deleting texture message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a position.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that the position should be deleted. The message includes
     * the current system time.
     *
     * @param id The ID of the entity whose position is to be deleted.
     * @return A network message indicating the deletion of the position.
     */
    rtype::network::Message<NetworkMessages> deletePositionMsg(size_t id)
    {
        // std::cout << "Deleting position message" << std::endl;
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

    /**
     * @brief Creates a network message to delete the velocity of an entity.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that the velocity of the entity should be deleted. The message
     * includes the current system time.
     *
     * @param id The ID of the entity whose velocity is to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteVelocityMsg(size_t id)
    {
        // std::cout << "Deleting velocity message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a health entity.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a health entity should be deleted. The message includes
     * the current system time.
     *
     * @param id The ID of the entity to be deleted.
     * @return A network message indicating the deletion of the specified health entity.
     */
    rtype::network::Message<NetworkMessages> deleteHealthMsg(size_t id)
    {
        // std::cout << "Deleting health message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a damage entity.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a damage entity should be deleted. The message includes
     * the current system time.
     *
     * @param id The ID of the entity to be deleted.
     * @return A network message containing the delete damage command and the entity ID.
     */
    rtype::network::Message<NetworkMessages> deleteDamageMsg(size_t id)
    {
        // std::cout << "Deleting damage message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a hitbox.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a hitbox should be deleted. The message includes the
     * current system time.
     *
     * @param id The ID of the entity whose hitbox is to be deleted.
     * @return A network message containing the delete hitbox command and the entity ID.
     */
    rtype::network::Message<NetworkMessages> deleteHitboxMsg(size_t id)
    {
        // std::cout << "Deleting hitbox message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a sprite.
     *
     * This function constructs a network message with the specified sprite ID
     * to indicate that the sprite should be deleted. The message includes the
     * sprite ID and the current system time.
     *
     * @param id The ID of the sprite to be deleted.
     * @return A network message containing the delete sprite command.
     */
    rtype::network::Message<NetworkMessages> deleteSpriteMsg(size_t id)
    {
        // std::cout << "Deleting sprite message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a transform.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a transform should be deleted. The message includes
     * the entity ID and the current system time.
     *
     * @param id The ID of the entity whose transform is to be deleted.
     * @return A network message containing the delete transform command.
     */
    rtype::network::Message<NetworkMessages> deleteTransformMsg(size_t id)
    {
        // std::cout << "Deleting transform message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a parent entity.
     *
     * This function constructs a network message with the specified entity ID
     * and the current system time. The message is intended to signal the deletion
     * of a parent entity in the network.
     *
     * @param id The ID of the entity to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteParentMsg(size_t id)
    {
        // std::cout << "Deleting parent message" << std::endl;
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

    /**
     * @brief Creates a network message to delete an input.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that an input should be deleted. The message includes the
     * current system time.
     *
     * @param id The ID of the entity whose input is to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteInputMsg(size_t id)
    {
        // std::cout << "Deleting input message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a type.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a type should be deleted. The message includes the
     * current system time.
     *
     * @param id The ID of the entity to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed delete type message.
     */
    rtype::network::Message<NetworkMessages> deleteTypeMsg(size_t id)
    {
        // std::cout << "Deleting type message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a cooldown.
     *
     * This function constructs a network message with the specified entity ID
     * and the current system time, indicating a request to delete a cooldown.
     *
     * @param id The ID of the entity for which the cooldown is to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteCooldownMsg(size_t id)
    {
        // std::cout << "Deleting cooldown message" << std::endl;
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

    /**
     * @brief Creates a network message containing size information.
     *
     * This function constructs a network message with the specified entity ID and size
     * components (x and y). The message is populated with the entity ID and size data,
     * and a timestamp is appended to the message body.
     *
     * @param id The unique identifier of the entity.
     * @param x The width component of the size.
     * @param y The height component of the size.
     * @return A network message containing the entity ID, size data, and a timestamp.
     */
    rtype::network::Message<NetworkMessages> createSizeMsg(size_t id, float x,
                                                          float y)
    {
        // std::cout << "Creating size message" << std::endl;
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

    /**
     * @brief Creates a network message to update the size of an entity.
     *
     * This function constructs a network message that contains the ID of the entity
     * and its new size (width and height). The message is then timestamped with the
     * current system time.
     *
     * @param id The ID of the entity to update.
     * @param x The new width of the entity.
     * @param y The new height of the entity.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateSizeMsg(size_t id, float x,
                                                          float y)
    {
        // std::cout << "Updating size message" << std::endl;
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

    /**
     * @brief Creates a network message to delete an entity size.
     *
     * This function constructs a network message with the specified entity ID
     * and the current timestamp. The message is intended to signal the deletion
     * of an entity size in the network.
     *
     * @param id The ID of the entity whose size is to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteSizeMsg(size_t id)
    {
        // std::cout << "Deleting size message" << std::endl;
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

    /**
     * @brief Creates a network message for AI creation.
     *
     * This function constructs a network message that contains information
     * about the creation of an AI entity. The message includes the entity ID,
     * AI type, and the current timestamp.
     *
     * @param id The unique identifier for the AI entity.
     * @param type The type of AI to be created.
     * @return A network message containing the AI creation details.
     */
    rtype::network::Message<NetworkMessages> createAIMsg(size_t id, AIType type)
    {
        // std::cout << "Creating AI message" << std::endl;
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

    /**
     * @brief Creates a network message to update an AI entity.
     *
     * This function constructs a network message that contains information
     * about an AI entity update. It includes the entity ID and AI type,
     * and appends the current system time to the message body.
     *
     * @param id The unique identifier of the AI entity.
     * @param type The type of AI component to update.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateAIMsg(size_t id, AIType type)
    {
        // std::cout << "Updating AI message" << std::endl;
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

    /**
     * @brief Creates a network message to delete an AI entity.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that an AI entity should be deleted. The message includes
     * the entity ID and the current system time.
     *
     * @param id The ID of the AI entity to be deleted.
     * @return A network message containing the delete AI command and the entity ID.
     */
    rtype::network::Message<NetworkMessages> deleteAIMsg(size_t id)
    {
        // std::cout << "Deleting AI message" << std::endl;
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

    /**
     * @brief Creates a network message for the menu.
     *
     * This function constructs a network message with the header ID set to
     * NetworkMessages::menu. It also appends the current system time to the message.
     *
     * @return rtype::network::Message<NetworkMessages> The constructed menu message.
     */
    rtype::network::Message<NetworkMessages> createMenuMsg()
    {
        // std::cout << "Creating menu message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::menu;
        // std::cout << "create menu" << std::endl;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a game message with the current system time.
     *
     * This function constructs a `rtype::network::Message` object with the
     * message header ID set to `NetworkMessages::game`. It also appends the
     * current system time to the message.
     *
     * @return A `rtype::network::Message<NetworkMessages>` object containing
     * the game message and the current system time.
     */
    rtype::network::Message<NetworkMessages> createGameMsg()
    {
        // std::cout << "Creating game message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::game;
        // std::cout << "create game" << std::endl;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a key bind network message.
     *
     * This function creates a network message with the ID set to `NetworkMessages::keyBind`.
     * It also includes the current system time in the message payload.
     *
     * @return rtype::network::Message<NetworkMessages> The created key bind network message.
     */
    rtype::network::Message<NetworkMessages> createKeyBindMsg()
    {
        // std::cout << "Creating keyBind message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::keyBind;
        // std::cout << "create keyBind" << std::endl;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a network message to delete a rectangle shape.
     *
     * This function constructs a network message that indicates a request to delete
     * a rectangle shape identified by the given ID. The message includes the entity ID
     * and the current system time.
     *
     * @param id The ID of the rectangle shape to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteRectangleShapeMsg(size_t id)
    {
        // std::cout << "Deleting rectangleShape message" << std::endl;
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

    /**
     * @brief Creates an onClick network message.
     *
     * This function constructs a network message of type `createOnClick` with the provided entity ID,
     * client number, and action. It serializes the entity ID and onClick component into the message body
     * and appends the current system time to the message.
     *
     * @param id The ID of the entity.
     * @param numClient The client number associated with the action.
     * @param action The action to be performed on click.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> createOnClickMsg(size_t id, int numClient, Action action)
    {
        // std::cout << "Creating onClick message" << std::endl;
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

    /**
     * @brief Creates a network message to update the onClick action for a specific entity.
     *
     * This function constructs a network message with the specified entity ID and action.
     * The message is then timestamped with the current system time.
     *
     * @param id The ID of the entity to update.
     * @param action The action to be performed on click.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateOnClickMsg(size_t id, Action action)
    {
        // std::cout << "Updating onClick message" << std::endl;
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

    /**
     * @brief Creates a network message to delete an entity on click.
     *
     * This function constructs a network message with the specified entity ID
     * and the current timestamp. The message is intended to signal the deletion
     * of an entity when it is clicked.
     *
     * @param id The ID of the entity to be deleted.
     * @return A network message containing the entity ID and the current timestamp.
     */
    rtype::network::Message<NetworkMessages> deleteOnClickMsg(size_t id)
    {
        // std::cout << "Deleting onClick message" << std::endl;
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

    /**
     * @brief Creates a network message containing text information.
     *
     * @param id The unique identifier for the entity.
     * @param x The x-coordinate of the text position.
     * @param y The y-coordinate of the text position.
     * @param font The font used for the text.
     * @param string The string content of the text.
     * @param size The size of the text.
     * @param color The color of the text.
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the text information.
     */
    rtype::network::Message<NetworkMessages> createTextMsg(size_t id, float x, float y, TextFont font, TextString string, int size, RColor color)
    {
        // std::cout << "Creating text message" << std::endl;
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

    /**
     * @brief Creates a network message to update text information.
     *
     * @param id The unique identifier of the entity.
     * @param x The x-coordinate of the text position.
     * @param y The y-coordinate of the text position.
     * @param font The font used for the text.
     * @param string The string content of the text.
     * @param size The size of the text.
     * @param color The color of the text.
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the updated text information.
     */
    rtype::network::Message<NetworkMessages> updateTextMsg(size_t id, float x, float y, TextFont font, TextString string, int size, RColor color)
    {
        // std::cout << "Updating text message" << std::endl;
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

    /**
     * @brief Creates a network message to delete a text entity.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a text entity should be deleted. The message includes
     * the current system time.
     *
     * @param id The ID of the text entity to be deleted.
     * @return A network message indicating the deletion of the specified text entity.
     */
    rtype::network::Message<NetworkMessages> deleteTextMsg(size_t id)
    {
        // std::cout << "Deleting text message" << std::endl;
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

    /**
     * @brief Creates a network message for playing a sound.
     *
     * This function constructs a network message that contains information about a sound to be played.
     * It includes the entity ID, sound path, and play status, and appends the current system time to the message.
     *
     * @param id The ID of the entity associated with the sound.
     * @param path The path to the sound file.
     * @param play A boolean indicating whether to play (true) or stop (false) the sound.
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the sound information.
     */
    rtype::network::Message<NetworkMessages> createSoundMsg(size_t id, SoundPath path, bool play)
    {
        // std::cout << "Creating sound message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createSound;
        EntityId entity = {id};
        SoundComponent sound = {path, play};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> soundBytes(reinterpret_cast<uint8_t *>(&sound),
                                        reinterpret_cast<uint8_t *>(&sound) + sizeof(SoundComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), soundBytes.begin(), soundBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a network message to update sound settings.
     *
     * This function constructs a network message that contains information about
     * updating sound settings for a specific entity. The message includes the entity ID,
     * the sound path, and whether the sound should be played or not.
     *
     * @param id The ID of the entity whose sound settings are being updated.
     * @param path The path to the sound file.
     * @param play A boolean indicating whether the sound should be played (true) or stopped (false).
     * @return rtype::network::Message<NetworkMessages> The constructed network message containing the sound update information.
     */
    rtype::network::Message<NetworkMessages> updateSoundMsg(size_t id, SoundPath path, bool play)
    {
        // std::cout << "Updating sound message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateSound;
        EntityId entity = {id};
        SoundComponent sound = {path, play};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> soundBytes(reinterpret_cast<uint8_t *>(&sound),
                                        reinterpret_cast<uint8_t *>(&sound) + sizeof(SoundComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), soundBytes.begin(), soundBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a network message to delete a sound.
     *
     * This function constructs a network message with the specified sound ID to
     * indicate that a sound should be deleted. The message includes the sound ID
     * and the current system time.
     *
     * @param id The ID of the sound to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteSoundMsg(size_t id)
    {
        // std::cout << "Deleting sound message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteSound;
        EntityId entity = {id};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a network message for playing or stopping music.
     *
     * This function constructs a network message that contains information about
     * a music action, including the entity ID, the sound path, and whether to play
     * or stop the music. The message is then timestamped with the current system time.
     *
     * @param id The ID of the entity associated with the music action.
     * @param path The file path of the sound to be played.
     * @param play A boolean indicating whether to play (true) or stop (false) the music.
     * @return A network message containing the music action details.
     */
    rtype::network::Message<NetworkMessages> createMusicMsg(size_t id, SoundPath path, bool play)
    {
        // std::cout << "Creating music message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::createMusic;
        EntityId entity = {id};
        SoundComponent music = {path, play};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> musicBytes(reinterpret_cast<uint8_t *>(&music),
                                        reinterpret_cast<uint8_t *>(&music) + sizeof(SoundComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), musicBytes.begin(), musicBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a network message to update the music state.
     *
     * This function constructs a network message that contains information about
     * updating the music state, including the entity ID, sound path, and play state.
     * The message is timestamped with the current system time.
     *
     * @param id The ID of the entity for which the music state is being updated.
     * @param path The path to the sound file.
     * @param play A boolean indicating whether to play or stop the music.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> updateMusicMsg(size_t id, SoundPath path, bool play)
    {
        // std::cout << "Updating music message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::updateMusic;
        EntityId entity = {id};
        SoundComponent music = {path, play};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        std::vector<uint8_t> musicBytes(reinterpret_cast<uint8_t *>(&music),
                                        reinterpret_cast<uint8_t *>(&music) + sizeof(SoundComponent));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        message.body.insert(message.body.end(), musicBytes.begin(), musicBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }

    /**
     * @brief Creates a network message to delete a music entity.
     *
     * This function constructs a network message with the specified entity ID
     * to indicate that a music entity should be deleted. The message includes
     * the current system time.
     *
     * @param id The ID of the music entity to be deleted.
     * @return rtype::network::Message<NetworkMessages> The constructed network message.
     */
    rtype::network::Message<NetworkMessages> deleteMusicMsg(size_t id)
    {
        // std::cout << "Deleting music message" << std::endl;
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::deleteMusic;
        EntityId entity = {id};
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entity),
                                         reinterpret_cast<uint8_t *>(&entity) + sizeof(EntityId));
        message.body.insert(message.body.end(), entityBytes.begin(), entityBytes.end());
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        message << timeNow;
        return message;
    }
};
