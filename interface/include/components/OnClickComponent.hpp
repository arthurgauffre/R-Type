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
        /**
         * @brief Constructs an OnClickComponent object.
         *
         * @param entityID The unique identifier for the entity associated with this component.
         * @param action The action to be performed when the component is clicked.
         * @param numClient The client number associated with this component.
         */
        OnClickComponent(uint32_t entityID, Action action, int numClient) : AComponent(entityID), _action(action), _numClient(numClient)
        {
        }

        /**
         * @brief Default destructor for the OnClickComponent class.
         */
        ~OnClickComponent() = default;

        /**
         * @brief Checks if the component has been clicked.
         *
         * @return true if the component is clicked, false otherwise.
         */
        bool getClicked() const { return _clicked; }

        /**
         * @brief Retrieves the action associated with this component.
         *
         * @return Action The action associated with this component (as a enum).
         */
        Action getAction() const { return _action; }

        /**
         * @brief Get the number of clients.
         *
         * @return int The number of clients.
         */
        int getNumClient() const { return _numClient; }

        /**
         * @brief Sets the clicked state of the component.
         *
         * @param clicked A boolean value indicating whether the component is clicked (true) or not (false).
         */
        void setClicked(bool clicked) { _clicked = clicked; }

        /**
         * @brief Updates the component based on the given action.
         *
         * @param action The action to be processed by the component.
         */
        void update(Action action);

    protected:
    private:
        /**
         * @brief Represents an action to be performed when the component is clicked.
         *
         * This member variable holds the action that should be executed when the
         * OnClickComponent is triggered. The default value is Action::NONE, indicating
         * that no action is set.
         */
        Action _action = Action::NONE;

        /**
         * @brief Indicates whether the component has been clicked.
         *
         * This boolean flag is set to true when the component is clicked,
         * and false otherwise.
         */
        bool _clicked = false;

        /**
         * @brief Represents the number of clients.
         */
        int _numClient = 0;
    };
}
