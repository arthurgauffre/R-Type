/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <graphics/Color.hpp>

namespace component {
class TextComponent : virtual public AComponent {
public:
    /**
     * @brief Constructs a new TextComponent object.
     *
     * @param entityID The unique identifier for the entity.
     * @param x The x-coordinate of the text.
     * @param y The y-coordinate of the text.
     * @param text The text to display.
     * @param size The size of the text.
     * @param color The color of the text.
     */
    TextComponent(uint32_t entityID, std::pair<float, float> position, std::string text, int size, RColor color, std::string fontPath, std::shared_ptr<IGraphic> graphic);

    /**
     * @brief Default destructor for the TextComponent class.
     */
    ~TextComponent() = default;

    /**
     * @brief Get the x position of the text.
     *
     * @return The x position as a float.
     */
    float getX() const { return _x; }

    /**
     * @brief Get the y position of the text.
     *
     * @return The y position as a float.
     */
    float getY() const { return _y; }

    /**
     * @brief Get the text to display.
     *
     * @return The text as a string.
     */
    std::string getText() const { return _text; }

    /**
     * @brief Get the size of the text.
     *
     * @return The size as an integer.
     */
    int getSize() const { return _size; }

    /**
     * @brief Get the color of the text.
     *
     * @return The color as an RColor.
     */
    RColor getColor() const { return _color; }

    /**
     * @brief Get the id of the text.
     *
     * @return The id as a size_t.
     */
    size_t getTextId() const { return _textId; }

    void update(std::pair<float, float> position, std::string text, int size, RColor color, std::shared_ptr<IGraphic> graphic);

private:
    /**
     * @brief Represents the idtext of the text.
     * 
     */
    size_t _textId;

    /**
     * @brief Represents the x-coordinate of the text.
     */
    float _x;

    /**
     * @brief Represents the y-coordinate of the text.
     */
    float _y;

    /**
     * @brief Represents the text to display.
     */
    std::string _text;

    /**
     * @brief Represents the size of the text.
     */
    int _size;

    /**
     * @brief Represents the color of the text.
     */
    RColor _color;
};
} // namespace component
