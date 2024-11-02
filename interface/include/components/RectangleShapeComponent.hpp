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
        /**
         * @brief Constructs a new RectangleShapeComponent object.
         *
         * @param entityID The unique identifier for the entity.
         * @param position A pair representing the x and y coordinates of the position.
         * @param size A pair representing the width and height of the rectangle.
         * @param color The color of the rectangle.
         * @param graphic A shared pointer to an IGraphic object for rendering.
         */
        RectangleShapeComponent(uint32_t entityID, std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic);

        /**
         * @brief Destructor for the RectangleShapeComponent class.
         *
         * This destructor is responsible for cleaning up any resources
         * allocated by the RectangleShapeComponent instance.
         */
        ~RectangleShapeComponent();

        /**
         * @brief Get the X coordinate of the rectangle shape.
         *
         * @return float The X coordinate.
         */
        float getX() const { return _x; }

        /**
         * @brief Get the Y coordinate of the rectangle shape.
         *
         * @return float The Y coordinate.
         */
        float getY() const { return _y; }

        /**
         * @brief Get the width of the rectangle shape.
         *
         * @return float The width of the rectangle shape.
         */
        float getWidth() const { return _width; }

        /**
         * @brief Get the height of the rectangle shape.
         *
         * @return float The height of the rectangle shape.
         */
        float getHeight() const { return _height; }

        /**
         * @brief Get the color of the rectangle shape.
         *
         * @return RColor The current color of the rectangle shape (rgba struct).
         */
        RColor getColor() const { return _color; }

        /**
         * @brief Get the ID of the rectangle shape.
         *
         * This function returns a reference to the ID of the rectangle shape
         * associated with this component.
         *
         * @return size_t& Reference to the rectangle shape ID.
         */
        size_t &getRectangleShapeId() { return _rectangleShapeId; }

        /**
         * @brief Updates the properties of the rectangle shape component.
         *
         * @param position A pair of floats representing the new position (x, y) of the rectangle.
         * @param size A pair of floats representing the new size (width, height) of the rectangle.
         * @param color An RColor object representing the new color of the rectangle.
         * @param graphic A shared pointer to an IGraphic object used for rendering the rectangle.
         */
        void update(std::pair<float, float> position, std::pair<float, float> size, RColor color, std::shared_ptr<IGraphic> graphic);

    private:
        /**
         * @brief The x-coordinate of the rectangle shape.
         */
        float _x;

        /**
         * @brief The y-coordinate of the rectangle shape.
         */
        float _y;

        /**
         * @brief The width of the rectangle shape.
         */
        float _width;

        /**
         * @brief Height of the rectangle shape.
         */
        float _height;

        /**
         * @brief The color of the rectangle shape.
         *
         * This member variable holds the color information for the rectangle shape component.
         * It is represented by an instance of the RColor struct (rgba).
         */
        RColor _color;

        /**
         * @brief Unique identifier for the rectangle shape component.
         */
        size_t _rectangleShapeId;
};
}
