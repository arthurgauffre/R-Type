/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TypeComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

#include <iostream>

namespace component
{
    class TypeComponent : public AComponent
    {
    public:
        TypeComponent(uint32_t entityID, std::string type);
        ~TypeComponent();

        std::string getType();
        void setType(std::string type);

        void update(float deltaTime) override {}

    private:
        std::string _type;
    };
}