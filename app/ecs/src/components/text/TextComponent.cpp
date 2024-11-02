/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextComponent
*/

#include <components/TextComponent.hpp>

namespace component
{
    /**
     * @brief Constructs a new TextComponent object.
     *
     * @param entityID The unique identifier for the entity.
     * @param position A pair representing the x and y coordinates of the text position.
     * @param text The string of text to be displayed.
     * @param size The font size of the text.
     * @param color The color of the text.
     * @param fontPath The file path to the font to be used.
     * @param graphic A shared pointer to the IGraphic interface for rendering the text.
     */
    TextComponent::TextComponent(uint32_t entityID, std::pair<float, float> position, std::string text, int size, RColor color, std::string fontPath, std::shared_ptr<IGraphic> graphic)
        : AComponent(entityID), _x(position.first), _y(position.second), _text(text), _size(size), _color(color), _fontPath(fontPath)
    {
        _textId = graphic->createText(text, fontPath, size, color);
        graphic->setTextPosition(position.first, position.second, _textId);
    };

    /**
     * @brief Updates the text component with new properties.
     *
     * @param position A pair of floats representing the new position (x, y) of the text.
     * @param text A string representing the new text to be displayed.
     * @param size An integer representing the new size of the text.
     * @param color An RColor object representing the new color of the text.
     * @param graphic A shared pointer to an IGraphic object used to update the text properties in the graphical context.
     */
    void TextComponent::update(std::pair<float, float> position, std::string text, int size, RColor color, std::shared_ptr<IGraphic> graphic)
    {
        _x = position.first;
        _y = position.second;
        _text = text;
        _size = size;
        _color = color;
        graphic->updateText(_textId, text, size, color);
        graphic->setTextPosition(_textId, position.first, position.second);
    }
} // namespace component