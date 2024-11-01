/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#include <graphics/SfmlGraphic.hpp>

SfmlGraphic::SfmlGraphic()
{
}

SfmlGraphic::~SfmlGraphic()
{
}

void SfmlGraphic::createWindow(int x, int y, std::string name)
{
    _window.create(sf::VideoMode(x, y), name);
}

size_t SfmlGraphic::createSprite()
{
    size_t id = _spritesId.size();
    _spritesId.push_back(id);
    _sprites[id] = sf::Sprite();
    return id;
}

size_t SfmlGraphic::createTexture(std::string path)
{
    size_t id = 0;

    if (_texturesId.find(path) != _texturesId.end())
        return _texturesId[path];
    else
        id = _textures.size();
    _texturesId[path] = id;
    _textures[id] = sf::Texture();
    _textures[id].loadFromFile(path);
    return id;
}

size_t SfmlGraphic::createRectangleShape(float x, float y)
{
    size_t id = _rectangleShapesId.size();
    _rectangleShapesId.push_back(id);
    _rectangleShapes[id] = sf::RectangleShape();
    _rectangleShapes[id].setSize(sf::Vector2f(x, y));
    return id;
}

void SfmlGraphic::setSpriteTexture(size_t spriteId, size_t textureId)
{
    _sprites[spriteId].setTexture(_textures[textureId]);
}

void SfmlGraphic::setSpritePosition(float x, float y, size_t id)
{
    _sprites[id].setPosition(x, y);
}

void SfmlGraphic::setSpriteScale(float x, float y, size_t id)
{
    _sprites[id].setScale(x, y);
}

void SfmlGraphic::setSpriteRotation(float angle, size_t id)
{
    _sprites[id].setRotation(angle);
}

void SfmlGraphic::setRectangleShapePosition(float x, float y, size_t id)
{
    _rectangleShapes[id].setPosition(x, y);
}

void SfmlGraphic::setRectangleShapeSize(float x, float y, size_t id)
{
    _rectangleShapes[id].setSize(sf::Vector2f(x, y));
}

void SfmlGraphic::setRectangleShapeRotation(float angle, size_t id)
{
    _rectangleShapes[id].setRotation(angle);
}

void SfmlGraphic::setRectangleShapeFillColor(int r, int g, int b, int a, size_t id)
{
    _rectangleShapes[id].setFillColor(sf::Color(r, g, b, a));
}

std::pair<float, float> SfmlGraphic::getTextureSize(size_t id)
{
    return std::make_pair(_textures[id].getSize().x, _textures[id].getSize().y);
}

void SfmlGraphic::drawSprite(size_t id)
{
    _window.draw(_sprites[id]);
}

void SfmlGraphic::drawRectangleShape(size_t id)
{
    _window.draw(_rectangleShapes[id]);
}

void SfmlGraphic::drawText(size_t id)
{
    _window.draw(_texts[id]);
}

void SfmlGraphic::eventHandler()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
}

bool SfmlGraphic::isKeyPressed(KeyBoard key)
{
    switch (key)
    {
    case KeyBoard::A:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    case KeyBoard::B:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::B);
    case KeyBoard::C:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    case KeyBoard::D:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    case KeyBoard::E:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    case KeyBoard::F:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    case KeyBoard::G:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::G);
    case KeyBoard::H:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::H);
    case KeyBoard::I:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::I);
    case KeyBoard::J:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::J);
    case KeyBoard::K:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::K);
    case KeyBoard::L:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::L);
    case KeyBoard::M:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::M);
    case KeyBoard::N:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::N);
    case KeyBoard::O:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::O);
    case KeyBoard::P:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
    case KeyBoard::Q:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    case KeyBoard::R:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    case KeyBoard::S:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    case KeyBoard::T:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::T);
    case KeyBoard::U:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::U);
    case KeyBoard::V:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::V);
    case KeyBoard::W:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    case KeyBoard::X:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    case KeyBoard::Y:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
    case KeyBoard::Z:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    case KeyBoard::Space:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    default:
        return false;
    }
}

bool SfmlGraphic::isMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

std::pair<float, float> SfmlGraphic::getMousePosition()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
    return std::make_pair(mousePosition.x, mousePosition.y);
}

void SfmlGraphic::windowDisplay()
{
    _window.display();
}

void SfmlGraphic::windowClear()
{
    _window.clear();
}

void SfmlGraphic::windowClose()
{
    _window.close();
}

size_t SfmlGraphic::createText(std::string text, std::string fontPath, int size, RColor color)
{
    size_t id = _textsId.size();
    _textsId.push_back(id);
    _texts[id] = sf::Text();
    _fonts[id] = sf::Font();
    _fonts[id].loadFromFile(fontPath);
    _texts[id].setFont(_fonts[id]);
    _texts[id].setString(text);
    _texts[id].setCharacterSize(size);
    _texts[id].setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    return id;
}

void SfmlGraphic::updateText(size_t id, std::string text, int size, RColor color)
{
    if (_texts.find(id) == _texts.end())
        return;
    _texts[id].setString(text);
    _texts[id].setCharacterSize(size);
    _texts[id].setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

EXPORT_API IGraphic *createGraphic()
{
    return new SfmlGraphic();
}