/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RectangleShapeComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <graphics/Color.hpp>

namespace component {
class RectangleShapeComponent: public AComponent {
    public:
        RectangleShapeComponent(uint32_t entityID, std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic);
        ~RectangleShapeComponent();

        float getX() const { return _x; }
        float getY() const { return _y; }

        float getWidth() const { return _width; }
        float getHeight() const { return _height; }

        RColor getColor() const { return _color; }

        size_t &getRectangleShapeId() { return _rectangleShapeId; }

        void update(std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic);

    private:
        float _x;
        float _y;
        float _width;
        float _height;
        RColor _color;
        size_t _rectangleShapeId;
};
}
