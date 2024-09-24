/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#pragma once

#pragma once

#include <vector>
#include <memory>
#include "ISystem.hpp"

namespace ECS_system
{
    class SystemManager
    {
    public:
        SystemManager() = default;
        ~SystemManager() = default;

        // Add a system
        template <typename T, typename... Args>
        T *addSystem(Args &&...args)
        {
            auto system = std::make_unique<T>(std::forward<Args>(args)...);
            T *systemPtr = system.get();
            systems.push_back(std::move(system));
            return systemPtr;
        }

        // Update all systems
        void update(float deltaTime, std::vector<std::unique_ptr<entity::IEntity>> entities);

    private:
        std::vector<std::unique_ptr<ISystem>> systems; // Vector of systems
    };
}
