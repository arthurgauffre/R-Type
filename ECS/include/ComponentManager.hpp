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
            components[entityID].push_back(std::move(component));
            return ptr;
        }

        template <typename T>
        T *getComponent(uint32_t entityID)
        {
            const auto &entityComponents = components[entityID];

            for (const auto &component : entityComponents)
            {
                if (T *casted = dynamic_cast<T *>(component.get()))
                    return casted;
            }
            return nullptr;
        }

        void update(float deltaTime);

    private:
        // Components stocked by entity ID
        std::unordered_map<uint32_t, std::vector<std::unique_ptr<IComponent>>> components;
    };
}
