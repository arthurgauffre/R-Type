/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AGraphic.hpp>

class SfmlGraphic : virtual public AGraphic {
    public:
        SfmlGraphic();
        ~SfmlGraphic();

        void createWindow(int x, int y, std::string name) override;
        size_t createSprite() override;
        size_t createTexture(std::string path) override;
        size_t createRectangleShape(float x, float y) override;

        void setSpriteTexture(size_t spriteId, size_t textureId) override;
        void setSpritePosition(float x, float y, size_t id) override;
        void setSpriteScale(float x, float y, size_t id) override;
        void setSpriteRotation(float angle, size_t id) override;

        void setRectangleShapePosition(float x, float y, size_t id) override;
        void setRectangleShapeSize(float x, float y, size_t id) override;
        void setRectangleShapeRotation(float angle, size_t id) override;
        void setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) override;

        std::pair<float, float> getTextureSize(size_t id) override;

        void drawSprite(size_t id) override;
        void drawRectangleShape(size_t id) override;

        void eventHandler() override;

        bool isMousePressed() override;
        std::pair<float, float> getMousePosition() override;

        void windowDisplay() override;
        void windowClear() override;
        void windowClose() override;
    protected:
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        std::unordered_map<size_t, sf::Sprite> _sprites;
        std::unordered_map<size_t, sf::Texture> _textures;
        std::unordered_map<size_t, sf::RectangleShape> _rectangleShapes;
        std::unordered_map<size_t, sf::Font> _fonts;
};
