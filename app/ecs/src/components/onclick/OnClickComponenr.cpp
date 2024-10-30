/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OnClickComponenr
*/

#include <components/OnClickComponent.hpp>

namespace component
{
    void OnClickComponent::onClick()
    {
        _clicked = true;
    }

    void OnClickComponent::update(Action action)
    {
        _action = action;
    }
} // namespace component