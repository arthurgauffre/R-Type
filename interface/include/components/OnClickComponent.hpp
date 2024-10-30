/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OnClickComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <r-type/Enum.hpp>

namespace component
{
    class OnClickComponent : public AComponent
    {
    public:
        OnClickComponent(uint32_t entityID, Action action)
            : AComponent(entityID), _action(action)
        {
        }
        ~OnClickComponent() = default;

        bool getClicked() const { return _clicked; }
        Action getAction() const { return _action; }
        
        void onClick();
        void update(Action action);

    protected:
    private:
        Action _action;
        bool _clicked = false;
    };
}
