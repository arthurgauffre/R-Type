/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OnClickComponent
*/

#include <components/OnClickComponent.hpp>

namespace component
{
    /**
     * @brief Updates the OnClickComponent with the specified action.
     *
     * @param action The action to be set for the OnClickComponent.
     */
    void OnClickComponent::update(Action action)
    {
        _action = action;
    }
} // namespace component