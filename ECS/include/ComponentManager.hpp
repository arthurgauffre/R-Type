/*
** EPITECH PROJECT, 2024
** *
** File description:
** ComponentManager
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "IComponent.hpp"
#include "IEntity.hpp"

namespace component
{
    class ComponentManager
    {
    public:
        template <typename T, typename... Args>
        T *addComponent(uint32_t entityID, Args &&...args)
        {
            auto component = std::make_unique<T>(entityID, std::forward<Args>(args)...);
            T *ptr = component.get();
            _components[entityID].push_back(std::move(component));
            return ptr;
        }

        template <typename T>
        T *getComponent(uint32_t entityID)
        {
            auto it = _components.find(entityID);
            if (it == _components.end())
                return nullptr;

            const auto &entityComponents = it->second;

            for (const auto &component : entityComponents)
            {
                if (T *casted = dynamic_cast<T *>(component.get()))
                    return casted;
            }
            return nullptr;
        }

        template <typename... Components>
        bool hasComponents(std::shared_ptr<entity::IEntity> entity)
        {
            return (... && (getComponent<Components>(entity->getID()) != nullptr));
        }

        template <typename... Components>
        std::vector<std::shared_ptr<entity::IEntity>> getEntitiesWithComponents(const std::vector<std::shared_ptr<entity::IEntity>> &entities)
        {
            std::vector<std::shared_ptr<entity::IEntity>> result;

            for (const auto &entity : entities)
            {
                if (entity && hasComponents<Components...>(entity))
                    result.push_back(entity);
            }

            return result;
        }

        void update(float deltaTime);

    private:
        // Components stocked by entity ID
        std::unordered_map<uint32_t, std::vector<std::unique_ptr<IComponent>>> _components;
    };
}
