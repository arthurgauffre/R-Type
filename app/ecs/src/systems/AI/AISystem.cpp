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
                         std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived)
    {
        for (auto &entity : entities)
        {
            component::TypeComponent *typeComponent = _componentManager.getComponent<component::TypeComponent>(entity->getID());
            component::AIComponent *aiComponent = _componentManager.getComponent<component::AIComponent>(entity->getID());
            component::VelocityComponent *velocityComponent = _componentManager.getComponent<component::VelocityComponent>(entity->getID());
            if (!typeComponent || !aiComponent || !velocityComponent)
                continue;
            if (typeComponent->getType() != component::Type::ENEMY)
                continue;
            if (aiComponent->getType() == component::AIType::LINEAR)
            {
                velocityComponent->setActualVelocityX(-velocityComponent->getActualVelocity().first);
            }
            else if (aiComponent->getType() == component::AIType::SINUSOIDAL)
            {
                // Définition de la vitesse de mouvement horizontal (vers la gauche)
                float horizontalSpeed = -50.0f; // ajustable pour la vitesse souhaitée vers la gauche

                // Amplitude et fréquence du mouvement sinusoïdal
                float amplitude = 30.0f; // ajustable pour définir la hauteur de la sinusoïde
                float frequency = 2.0f;  // ajustable pour définir la fréquence de la sinusoïde

                // Calcul de la vitesse actuelle en fonction de la sinusoïde
                float verticalSpeed = amplitude * std::sin(frequency * aiComponent->getElapsedTime());

                // Met à jour `ActualVelocity` dans le VelocityComponent
                velocityComponent->setActualVelocityX(horizontalSpeed);
                velocityComponent->setActualVelocityY(verticalSpeed);

                // Incrémente le temps pour la prochaine mise à jour
                aiComponent->setElapsedTime(deltaTime + aiComponent->getElapsedTime());
            }
            else if (aiComponent->getType() == component::AIType::CIRCULAR)
            {
                // Do something
            }
        }
    }
}