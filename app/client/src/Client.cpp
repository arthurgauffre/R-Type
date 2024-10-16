/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include <Client.hpp>

namespace rtype
{
    namespace network
    {
        void Client::run()
        {
            std::vector<std::string> msgToSend;
            sf::Clock clock;
            while (true)
            {
                if (IsConnected())
                {
                    if (!GetIncomingMessages().empty())
                    {
                        std::cout << "Incoming" << std::endl;
                        rtype::network::Message<NetworkMessages> msg = GetIncomingMessages().popFront().message;
                        handdleMessage(msg);
                    }
                }
                else
                {
                    std::cout << "Server Down" << std::endl;
                    break;
                }
                float deltaTime = clock.restart().asSeconds();
                msgToSend = _coreModule.get()->getSystemManager()->update(
                    deltaTime, _coreModule.get()->getEntityManager()->getEntities(),
                    msgToSend);
            }
        };

        // merge it with server
        std::string Client::GetTexturePath(TexturePath texture)
        {
            switch (texture)
            {
            case TexturePath::Background:
            {
                return "app/assets/images/city_background.png";
            }
            break;
            case TexturePath::Player:
            {
                return "app/assets/sprites/plane.png";
            }
            break;
                // case TexturePath::Enemy:
                // return "assets/enemy.png";
            }
            return "";
        }

        KeyAction Client::getAction(std::string action)
        {
            if (action == "moveUp")
                return KeyAction::moveUp;
            if (action == "moveDown")
                return KeyAction::moveDown;
            if (action == "moveLeft")
                return KeyAction::moveLeft;
            if (action == "moveRight")
                return KeyAction::moveRight;
            if (action == "shoot")
                return KeyAction::shoot;
            return KeyAction::moveUp;
        }

        void Client::handdleMessage(rtype::network::Message<NetworkMessages> &msg)
        {
            switch (msg.header.id)
            {
            case NetworkMessages::ServerAcceptance:
            {
                std::cout << "Server Accepted Connection" << std::endl;
            }
            break;

            case NetworkMessages::ServerPing:
            {
                std::chrono::system_clock::time_point timeNow =
                    std::chrono::system_clock::now();
                std::chrono::system_clock::time_point timeThen;
                msg >> timeThen;
                std::cout << "Ping: "
                          << std::chrono::duration<double>(timeNow - timeThen).count()
                          << std::endl;
            }
            break;
            case NetworkMessages::ServerMessage:
            {
                uint32_t clientID;
                msg >> clientID;
                std::cout << "Hello from [" << clientID << "]" << std::endl;
            }
            break;
            case NetworkMessages::ServerDenial:
            {
            }
            break;
            case NetworkMessages::MessageAll:
            {
            }
            break;
            case NetworkMessages::ClientConnection:
            {
            }
            break;
            case NetworkMessages::createEntity:
            {
                std::cout << "Entity created" << std::endl;
                EntityId entity;
                std::memcpy(&entity, msg.body.data(), sizeof(EntityId));

                std::cout << "Entity id: " << entity.id << std::endl;
                _coreModule.get()->getEntityManager()->createEntity(entity.id);
            }
            break;
            case NetworkMessages::destroyEntity:
            {
                std::cout << "Entity destroyed" << std::endl;
                EntityId entity;
                std::memcpy(&entity, msg.body.data(), sizeof(EntityId));
                std::cout << "Entity id: " << entity.id << std::endl;
                _coreModule.get()->getEntityManager()->destroyEntity(entity.id);
            }
            break;
            case NetworkMessages::createPosition:
            {
                std::cout << "Position component created" << std::endl;
                PositionComponent pos;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&pos, msg.body.data() + sizeof(EntityId), sizeof(PositionComponent));
                std::cout << "Position: " << pos.x << " " << pos.y << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::PositionComponent>(id.id, pos.x, pos.y);
            }
            break;
            case NetworkMessages::createSprite:
            {
                std::cout << "Sprite component created" << std::endl;
                SpriteComponent sprite;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&sprite, msg.body.data() + sizeof(EntityId), sizeof(SpriteComponent));
                std::cout << "Sprite: " << sprite.x << " " << sprite.y << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::SpriteComponent>(id.id, sprite.x, sprite.y);
            }
            break;
            case NetworkMessages::createTexture:
            {
                std::cout << "Texture component created" << std::endl;
                TextureComponent texture;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&texture, msg.body.data() + sizeof(EntityId), sizeof(TextureComponent));
                _coreModule.get()->getComponentManager()->addComponent<component::TextureComponent>(id.id, GetTexturePath(texture.texturePath));
            }
            break;
            case NetworkMessages::createTransform:
            {
                std::cout << "Transform component created" << std::endl;
                TransformComponent transform;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&transform, msg.body.data() + sizeof(EntityId), sizeof(TransformComponent));
                std::cout << "Transform: " << transform.x << " " << transform.y << " " << transform.scaleX << " " << transform.scaleY << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::TransformComponent>(id.id, sf::Vector2f(transform.x, transform.y), sf::Vector2f(transform.scaleX, transform.scaleY));
            }
            break;
            case NetworkMessages::createBackground:
            {
                std::cout << "Background component created" << std::endl;
                BackgroundComponent background;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&background, msg.body.data() + sizeof(EntityId), sizeof(BackgroundComponent));
                std::cout << "Background: " << background.x << " " << background.y << std::endl;
                std::cout << "Texture: " << GetTexturePath(background.texturePath) << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::BackgroundComponent>(id.id, GetTexturePath(background.texturePath), sf::Vector2f(background.x, background.y));
            }
            break;
            case NetworkMessages::createVelocity:
            {
                std::cout << "Velocity component created" << std::endl;
                VelocityComponent velocity;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&velocity, msg.body.data() + sizeof(EntityId), sizeof(VelocityComponent));
                std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::VelocityComponent>(id.id, sf::Vector2f(velocity.x, velocity.y));
            }
            break;
            case NetworkMessages::createParent:
            {
                std::cout << "Parent component created" << std::endl;
                ParentComponent parent;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&parent, msg.body.data() + sizeof(EntityId), sizeof(ParentComponent));
                std::cout << "Parent: " << parent.parentID << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::ParentComponent>(id.id, parent.parentID);
            }
            break;
            case NetworkMessages::createScroll:
            {
                std::cout << "Scroll component created" << std::endl;
                ScrollComponent scroll;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&scroll, msg.body.data() + sizeof(EntityId), sizeof(ScrollComponent));
                std::cout << "Scroll: " << scroll.x << " " << scroll.y << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::ScrollComponent>(id.id, sf::Vector2f(scroll.x, scroll.y));
            }
            break;
            case NetworkMessages::createHealth:
            {
                std::cout << "Health component created" << std::endl;
                HealthComponent health;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&health, msg.body.data() + sizeof(EntityId), sizeof(HealthComponent));
                std::cout << "Health: " << health.health << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::HealthComponent>(id.id, health.health);
            }
            break;
            case NetworkMessages::createDamage:
            {
                std::cout << "Damage component created" << std::endl;
                DamageComponent damage;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&damage, msg.body.data() + sizeof(EntityId), sizeof(DamageComponent));
                std::cout << "Damage: " << damage.damage << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::DamageComponent>(id.id, damage.damage);
            }
            break;
            case NetworkMessages::createHitbox:
            {
                std::cout << "Hitbox component created" << std::endl;
                HitboxComponent hitbox;
                EntityId id;
                std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId), sizeof(HitboxComponent));
                std::cout << "Hitbox: " << hitbox.x << " " << hitbox.y << std::endl;
                _coreModule.get()->getComponentManager()->addComponent<component::HitBoxComponent>(id.id, hitbox.x, hitbox.y);
            }
                // case NetworkMessages::createMusic:
                // {
                //     std::cout << "Music component created" << std::endl;
                //     MusicComponent music;
                //     EntityId id;
                //     std::memcpy(&id, msg.body.data(), sizeof(EntityId));
                //     std::memcpy(&music, msg.body.data() + sizeof(EntityId), sizeof(MusicComponent));
                //     std::cout << "Music: " << music.musicPath << std::endl;
                //     _coreModule.get()->getComponentManager()->addComponent<component::MusicComponent>(id.id, music.musicPath);
                // }
                // break;
            }
        }
    }
}
