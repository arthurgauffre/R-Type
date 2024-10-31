/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OnClickComponent
*/

#include <components/OnClickComponent.hpp>

namespace component
{
    void OnClickComponent::update(Action action)
    {
        _action = action;
    }
} // namespace component