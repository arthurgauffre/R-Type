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
        OnClickComponent(uint32_t entityID, Action action, int numClient) : AComponent(entityID), _action(action), _numClient(numClient)
        {
        }
        ~OnClickComponent() = default;

        bool getClicked() const { return _clicked; }
        Action getAction() const { return _action; }
        int getNumClient() const { return _numClient; }
        
        void onClick();
        void update(Action action);

    protected:
    private:
        Action _action = Action::NONE;
        bool _clicked = false;
        int _numClient = 0;
    };
}
