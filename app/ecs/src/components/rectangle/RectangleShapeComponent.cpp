/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RectangleShapeComponent
*/

#include <components/RectangleShapeComponent.hpp>

namespace component
{

    /**
     * @brief Constructs a new RectangleShapeComponent object.
     *
     * @param entityID The unique identifier for the entity.
     * @param position A pair representing the x and y coordinates of the rectangle's position.
     * @param size A pair representing the width and height of the rectangle.
     * @param color The color of the rectangle.
     * @param graphic A shared pointer to an IGraphic object used to create the rectangle shape.
     */
    RectangleShapeComponent::RectangleShapeComponent(uint32_t entityID, std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic)
        : AComponent(entityID), _x(position.first), _y(position.second), _width(size.first), _height(size.second), _color(color)
    {
        _rectangleShapeId = graphic->createRectangleShape(size.first, size.second);
    }

    /**
     * @brief Destructor for the RectangleShapeComponent class.
     *
     * This destructor is responsible for cleaning up any resources
     * that the RectangleShapeComponent may have acquired during its
     * lifetime. Currently, it does not perform any specific actions.
     */
    RectangleShapeComponent::~RectangleShapeComponent()
    {
    }

    /**
     * @brief Updates the properties of the rectangle shape component.
     *
     * This function updates the position, size, and color of the rectangle shape component
     * and applies these changes to the associated graphic object.
     *
     * @param position A pair of floats representing the new position (x, y) of the rectangle.
     * @param size A pair of floats representing the new size (width, height) of the rectangle.
     * @param color An RColor object representing the new color (RGBA) of the rectangle.
     * @param graphic A shared pointer to an IGraphic object used to apply the changes to the rectangle shape.
     */
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
} // namespace component
