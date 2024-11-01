/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AISystem
*/

#include <systems/AISytem.hpp>

namespace ECS_system
{
    void AISytem::update(float deltaTime,
                         std::vector<std::shared_ptr<entity::IEntity>> entities,
                         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
    {
        // lock the entity mutex
        std::lock_guard<std::mutex> lock(entityMutex);
        for (auto &entity : entities)
        {
            if (entity->getSceneStatus() != *sceneStatus && entity->getSceneStatus() != Scene::ALL)
                continue;
            component::TypeComponent *typeComponent = _componentManager.getComponent<component::TypeComponent>(entity->getID());
            component::AIComponent *aiComponent = _componentManager.getComponent<component::AIComponent>(entity->getID());
            component::VelocityComponent *velocityComponent = _componentManager.getComponent<component::VelocityComponent>(entity->getID());
            if (!typeComponent || !aiComponent || !velocityComponent)
                continue;
            if (typeComponent->getType() != Type::ENEMY)
                continue;
            if (aiComponent->getType() == AIType::LINEAR)
            {
                velocityComponent->setActualVelocityX(velocityComponent->getVelocity().first);
            }
            else if (aiComponent->getType() == AIType::SINUSOIDAL)
            {
                float horizontalSpeed = velocityComponent->getVelocity().first;

                float amplitude = 100.0f;
                float frequency = 2.0f;

                float verticalSpeed = amplitude * std::sin(frequency * aiComponent->getElapsedTime());

                velocityComponent->setActualVelocityX(horizontalSpeed);
                velocityComponent->setActualVelocityY(verticalSpeed);

                aiComponent->setElapsedTime(deltaTime + aiComponent->getElapsedTime());
            }
            else if (aiComponent->getType() == AIType::CIRCULAR)
            {
                float radius = 100.0f;
                float angularSpeed = 0.5f;

                float x = radius * std::cos(angularSpeed * aiComponent->getElapsedTime());
                float y = radius * std::sin(angularSpeed * aiComponent->getElapsedTime());

                velocityComponent->setActualVelocityX(x);
                velocityComponent->setActualVelocityY(y);

                aiComponent->setElapsedTime(deltaTime + aiComponent->getElapsedTime());
            }
        }
    }
}

extern "C" ECS_system::ISystem *createSystem(component::ComponentManager &componentManager,
                                             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom)
{
    return new ECS_system::AISytem(componentManager, entityManager, graphic, stringCom);
}