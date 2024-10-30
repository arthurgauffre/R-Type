/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AGraphic
*/

#pragma once

#include <r-type/IGraphic.hpp>

class AGraphic: virtual public IGraphic {
    public:
        AGraphic(): IGraphic(){};
        virtual ~AGraphic() = default;

        virtual void createWindow(int x, int y, std::string name) = 0;
        virtual size_t createSpirit() = 0;
    protected:
    private:
};