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
    private:
};