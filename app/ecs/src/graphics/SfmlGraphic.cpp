/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#include <graphics/SfmlGraphic.hpp>

SfmlGraphic::SfmlGraphic()
{
}

SfmlGraphic::~SfmlGraphic()
{
}

void SfmlGraphic::createWindow(int x, int y, std::string name)
{
    _window.create(sf::VideoMode(x, y), name);
}

size_t SfmlGraphic::createSpirit()
{
    return 0;
}