/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IGraphic
*/

#pragma once

#include <iostream>
#include <unordered_map>

class IGraphic {
    public:
        IGraphic();
        ~IGraphic();

        virtual void createWindow(int x, int y, std::string name) = 0;
        virtual size_t createSpirit() = 0;

    protected:
        std::vector<size_t> _sprites;
        std::unordered_map<std::string, size_t> _textures;
        std::unordered_map<std::string, size_t> _fonts;
    private:

};
