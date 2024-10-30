/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RectangleShapeComponent
*/

#include <components/RectangleShapeComponent.hpp>

namespace component {
RectangleShapeComponent::RectangleShapeComponent(uint32_t entityID, std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic)
    : AComponent(entityID), _x(position.first), _y(position.second), _width(size.first), _height(size.second), _color(color)
{
    _rectangleShapeId = graphic->createRectangleShape(size.first, size.second);
}

RectangleShapeComponent::~RectangleShapeComponent()
{
}

void RectangleShapeComponent::update(std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic)
{
    _x = position.first;
    _y = position.second;
    _width = size.first;
    _height = size.second;
    _color = color;
    graphic->setRectangleShapePosition(position.first, position.second, _rectangleShapeId);
    graphic->setRectangleShapeSize(size.first, size.second, _rectangleShapeId);
    graphic->setRectangleShapeFillColor(color.r, color.g, color.b, color.a, _rectangleShapeId);
}
}
