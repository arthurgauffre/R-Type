/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#include <iostream>
#include <systems/WeaponSystem.hpp>

ECS_system::WeaponSystem::WeaponSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom)
    : ASystem(componentManager, entityManager, graphic, audio, stringCom) {}

ECS_system::WeaponSystem::~WeaponSystem() {}

void ECS_system::WeaponSystem::createProjectile(
    uint32_t parentID, std::string texturePath,
    std::pair<float, float> velocity, std::pair<float, float> scale,
    int damage)
{
    uint32_t projectileID = _entityManager.generateEntityID();
    entity::IEntity *projectile = _entityManager.createEntity(projectileID, -1);

    if (_componentManager.getComponent<component::TypeComponent>(parentID)
            ->getType() == Type::PLAYER)
        _componentManager.addComponent<component::TypeComponent>(
            projectileID, Type::PLAYER_PROJECTILE);
    else
        _componentManager.addComponent<component::TypeComponent>(projectileID,
                                                                 Type::ENEMY_PROJECTILE);
    _componentManager.addComponent<component::DamageComponent>(projectileID,
                                                               damage);
    _componentManager.addComponent<component::ParentComponent>(projectileID,
                                                               parentID);
    _componentManager.addComponent<component::VelocityComponent>(
        projectileID, velocity, velocity);
    component::TextureComponent *texture = _componentManager.addComponent<component::TextureComponent>(
        projectileID, texturePath, _graphic);
    _componentManager.addComponent<component::HitBoxComponent>(
        projectileID, _graphic->getTextureSize(texture->getTexture()).first,
        _graphic->getTextureSize(texture->getTexture()).second);

    component::TransformComponent *transformPlayer =
        _componentManager.getComponent<component::TransformComponent>(parentID);
    component::TextureComponent *textureP =
        _componentManager.getComponent<component::TextureComponent>(parentID);

    std::pair<float, float> position = {
        transformPlayer->getPosition().first +
            _graphic->getTextureSize(textureP->getTexture()).first * transformPlayer->getScale().first,
        transformPlayer->getPosition().second +
            (_graphic->getTextureSize(textureP->getTexture()).second * transformPlayer->getScale().second) /
                2};

    if (_componentManager.getComponent<component::TypeComponent>(parentID)
            ->getType() == Type::ENEMY)
        position.first -=
            _graphic->getTextureSize(textureP->getTexture()).first * transformPlayer->getScale().first;

    component::TransformComponent *transformComponent =
        _componentManager.addComponent<component::TransformComponent>(
            projectileID, position, scale);
    _componentManager.addComponent<component::SpriteComponent>(
        projectileID, position.first, position.second, _graphic);

    if (_componentManager.getComponent<component::TypeComponent>(parentID)
            ->getType() == Type::ENEMY)
        transformComponent->setRotation(180);
}

void ECS_system::WeaponSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
{
    for (auto &entity :
         _componentManager.getEntitiesWithComponents<component::WeaponComponent>(
             entities))
    {
        if (entity->getSceneStatus() != *sceneStatus && entity->getSceneStatus() != Scene::ALL)
            continue;
        component::WeaponComponent *weaponComponent =
            _componentManager.getComponent<component::WeaponComponent>(
                entity->getID());
        component::CooldownComponent *cooldownComponent =
            _componentManager.getComponent<component::CooldownComponent>(
                weaponComponent->getWeaponEntityID());
        Type entityType =
            _componentManager
                .getComponent<component::TypeComponent>(entity->getID())
                ->getType();
        component::DamageComponent *damageComponent =
            _componentManager.getComponent<component::DamageComponent>(
                weaponComponent->getWeaponEntityID());

        if (!damageComponent || !cooldownComponent || !weaponComponent)
            continue;

        if (weaponComponent->getIsFiring() &&
            cooldownComponent->getTimeRemaining() > 0)
            weaponComponent->setIsFiring(false);

        if (cooldownComponent->getTimeRemaining() <= 0 && entityType == Type::ENEMY)
            weaponComponent->setIsFiring(true);

        float weaponVelocity = weaponComponent->getVelocity();
        if (weaponComponent->getIsFiring())
        {
            std::pair<float, float> projectileVelocity =
                std::pair<float, float>(weaponVelocity, 0);
            this->createProjectile(
                weaponComponent->getEntityID(), "app/assets/sprites/projectile.gif",
                projectileVelocity, std::pair<float, float>(1, 1), damageComponent->getDamage());

            cooldownComponent->setTimeRemaining(cooldownComponent->getCooldown());

            if (entityType == Type::PLAYER)
            {
                component::SoundComponent *soundComponent =
                    _componentManager.getComponent<component::SoundComponent>(
                        weaponComponent->getWeaponEntityID());
                if (soundComponent) {
                    soundComponent->setShouldPlay(true);
                    soundComponent->setCommunication(component::ComponentCommunication::UPDATE);
                }
                weaponComponent->setIsFiring(false);
            }
        }
    }
}

/**
 * @brief Factory function to create a new WeaponSystem.
 *
 * This function creates and returns a new instance of the WeaponSystem class.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 * @param graphic Shared pointer to an IGraphic instance.
 * @param stringCom StringCom instance for communication.
 *
 * @return Pointer to the newly created WeaponSystem instance.
 */
EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom)
{
    return new ECS_system::WeaponSystem(componentManager, entityManager, graphic, audio, stringCom);
}