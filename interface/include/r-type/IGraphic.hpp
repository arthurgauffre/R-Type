/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IGraphic
*/

#pragma once

#ifdef _WIN32
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C"
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include <r-type/Enum.hpp>
#include <graphics/Color.hpp>

class IGraphic {
    public:
        IGraphic(){};
        virtual ~IGraphic() = default;

        virtual void createWindow(int x, int y, std::string name) = 0;
        virtual size_t createSprite() = 0;
        virtual size_t createTexture(std::string path) = 0;
        virtual size_t createRectangleShape(float x, float y) = 0;

        virtual void setSpriteTexture(size_t spriteId, size_t textureId) = 0;
        virtual void setSpritePosition(float x, float y, size_t id) = 0;
        virtual void setSpriteScale(float x, float y, size_t id) = 0;
        virtual void setSpriteRotation(float angle, size_t id) = 0;

        virtual void setRectangleShapePosition(float x, float y, size_t id) = 0;
        virtual void setRectangleShapeSize(float x, float y, size_t id) = 0;
        virtual void setRectangleShapeRotation(float angle, size_t id) = 0;
        virtual void setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) = 0;

        virtual std::pair<float, float> getTextureSize(size_t id) = 0;

        virtual void drawSprite(size_t id) = 0;
        virtual void drawRectangleShape(size_t id) = 0;
        virtual void drawText(size_t id) = 0;

        virtual void eventHandler() = 0;

        virtual bool isKeyPressed(KeyBoard key) = 0;

        virtual bool isMousePressed() = 0;
        virtual std::pair<float, float> getMousePosition() = 0;

        virtual void windowDisplay() = 0;
        virtual void windowClear() = 0;
        virtual void windowClose() = 0;

        virtual size_t createText(std::string text, std::string fontPath, int size, RColor color) = 0;
        virtual void updateText(size_t id, std::string text, int size, RColor color) = 0;

    protected:
        std::vector<size_t> _spritesId;
        std::vector<size_t> _textsId;
        std::unordered_map<std::string, size_t> _texturesId;
        std::unordered_map<std::string, size_t> _fontsId;
        std::vector<size_t> _rectangleShapesId;
    private:

};
