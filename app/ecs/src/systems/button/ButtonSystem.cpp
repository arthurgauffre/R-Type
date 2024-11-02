/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ButtonComponent
*/

#include <systems/ButtonSystem.hpp>

namespace ECS_system {
    ButtonSystem::ButtonSystem(
        component::ComponentManager &componentManager,
        entity::EntityManager &entityManager,
        std::shared_ptr<IGraphic> graphic, StringCom stringCom)
        : ASystem(componentManager, entityManager, graphic, stringCom)
    {
    }

    void ButtonSystem::update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
    {
        std::lock_guard<std::mutex> lock(entityMutex);
        for (auto &entity : _componentManager.getEntitiesWithComponents<component::OnClickComponent,
        component::RectangleShapeComponent, component::TransformComponent>(entities)) {
            if (entity->getSceneStatus() != *sceneStatus && entity->getSceneStatus() != Scene::ALL)
                continue;
            component::OnClickComponent *onClick = _componentManager.getComponent<component::OnClickComponent>(entity->getID());
            component::RectangleShapeComponent *rectangle = _componentManager.getComponent<component::RectangleShapeComponent>(entity->getID());
            if (_graphic->isMousePressed())
                onClick->setClicked(true);
            std::pair<float, float> mousePos = _graphic->getMousePosition();
            if (mousePos.first >= rectangle->getX() && mousePos.first <= rectangle->getX() + rectangle->getWidth() &&
                mousePos.second >= rectangle->getY() && mousePos.second <= rectangle->getY() + rectangle->getHeight()) {
                if (onClick->getClicked()) {
                    onClick->setClicked(false);
                    msgToSend.push_back(std::make_pair(onClick->getAction(), entity->getID()));
                }
            }
            if (onClick->getClicked())
                onClick->setClicked(false);
        }
    }
}

/**
 * @brief Factory function to create a new ButtonSystem.
 *
 * This function creates and returns a new instance of the ButtonSystem class.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 * @param graphic Shared pointer to an IGraphic instance.
 * @param stringCom StringCom instance for string communication.
 *
 * @return Pointer to the newly created ButtonSystem instance.
 */
EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom) {
  return new ECS_system::ButtonSystem(componentManager, entityManager, graphic, stringCom);
}