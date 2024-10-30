/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/IGraphic.hpp>

class SfmlGraphic: virtual public IGraphic {
    public:
        SfmlGraphic();
        ~SfmlGraphic();

        void createWindow(int x, int y, std::string name) override;
        size_t createSpirit() override;

    protected:
    private:
        sf::RenderWindow _window;
        std::unordered_map<size_t, sf::Sprite> _sprites;
        std::unordered_map<size_t, sf::Texture> _textures;
        std::unordered_map<size_t, sf::Font> _fonts;
};
