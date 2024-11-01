/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextComponent
*/

#include <components/TextComponent.hpp>

namespace component {
TextComponent::TextComponent(uint32_t entityID, std::pair<float, float> position, std::string text, int size, RColor color, std::string fontPath, std::shared_ptr<IGraphic> graphic)
    : AComponent(entityID), _x(position.first), _y(position.second), _text(text), _size(size), _color(color), _fontPath(fontPath){
        _textId = graphic->createText(text, fontPath, size, color);
        graphic->setTextPosition(position.first, position.second, _textId);
    };

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