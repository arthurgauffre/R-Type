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
#include "Icomponent.hpp"

namespace component
{
    class ComponentManager
    {
    public:
        template <typename T, typename... Args>
        T *AddComponent(uint32_t entityID, Args &&...args);

        template <typename T>
        T *GetComponent(uint32_t entityID);

        void update(float deltaTime);

    private:
        // Components stocked by entity ID
        std::unordered_map<uint32_t, std::vector<std::unique_ptr<IComponent>>> components;
    };
}
