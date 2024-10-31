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
        std::shared_ptr<IGraphic> graphic)
        : ASystem(componentManager, entityManager, graphic)
    {
    }

    void ButtonSystem::update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
    {
        std::lock_guard<std::mutex> lock(entityMutex);
        for (auto &entity : _componentManager.getEntitiesWithComponents<component::OnClickComponent,
        component::RectangleShapeComponent, component::TransformComponent>(entities)) {
            if (entity->getSceneStatus() != *sceneStatus)
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

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic) {
  return new ECS_system::ButtonSystem(componentManager, entityManager, graphic);
}