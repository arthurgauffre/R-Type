/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AISystem
*/

#include <systems/AISytem.hpp>

namespace ECS_system
{
    /**
     * @brief Updates the AI system for all entities.
     *
     * This function updates the AI system for all entities by iterating through the list of entities,
     * checking their scene status, and updating their velocity based on their AI type.
     *
     * @param deltaTime The time elapsed since the last update.
     * @param entities A vector of shared pointers to entities.
     * @param msgToSend A reference to a vector of pairs containing actions and entity IDs to send messages.
     * @param msgReceived A reference to a vector of pairs containing received messages and their associated entity IDs.
     * @param entityMutex A mutex to ensure thread safety when accessing entities.
     * @param sceneStatus A shared pointer to the current scene status.
     */
    void AISytem::update(float deltaTime,
                         std::vector<std::shared_ptr<entity::IEntity>> entities,
                         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
    {
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

/**
 * @brief Factory function to create an AISystem.
 *
 * This function is used to create an instance of the AISystem class.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 * @param graphic Shared pointer to an IGraphic instance.
 * @param stringCom StringCom instance for communication.
 * @return Pointer to the newly created AISystem instance.
 */
extern "C" ECS_system::ISystem *createSystem(component::ComponentManager &componentManager,
                                             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom)
{
    return new ECS_system::AISytem(componentManager, entityManager, graphic, audio, stringCom);
}