/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#include <graphics/SfmlGraphic.hpp>

/**
 * @brief Default constructor for the SfmlGraphic class.
 *
 * This constructor initializes an instance of the SfmlGraphic class.
 */
SfmlGraphic::SfmlGraphic()
{
}

/**
 * @brief Destructor for the SfmlGraphic class.
 *
 * This destructor is responsible for cleaning up any resources
 * that the SfmlGraphic object may have acquired during its lifetime.
 */
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

void SfmlGraphic::setSpriteColor(size_t id, RColor color)
{
    _sprites[id].setColor(sf::Color(color.r, color.g, color.b, color.a));
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
    case KeyBoard::escape:
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    default:
        return false;
    }
}

KeyBoard SfmlGraphic::getKeyPressed()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return KeyBoard::A;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        return KeyBoard::B;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        return KeyBoard::C;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return KeyBoard::D;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        return KeyBoard::E;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        return KeyBoard::F;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        return KeyBoard::G;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        return KeyBoard::H;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        return KeyBoard::I;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        return KeyBoard::J;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        return KeyBoard::K;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        return KeyBoard::L;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return KeyBoard::M;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        return KeyBoard::N;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        return KeyBoard::O;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        return KeyBoard::P;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return KeyBoard::Q;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return KeyBoard::R;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return KeyBoard::S;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        return KeyBoard::T;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
        return KeyBoard::U;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        return KeyBoard::V;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return KeyBoard::W;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        return KeyBoard::X;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        return KeyBoard::Y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        return KeyBoard::Z;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return KeyBoard::Space;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return KeyBoard::escape;
    return KeyBoard::Unknown;
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
    size_t idText = _textsId.size();
    size_t idFont = _fontsId.size();

    _textsId.push_back(idText);
    _texts[idText] = sf::Text();
    if (_fontsId.find(fontPath) != _fontsId.end()) {
        idFont = _fontsId[fontPath];
    } else {
        _fontsId[fontPath] = idFont;
        _fonts[idText] = sf::Font();
        _fonts[idText].loadFromFile(fontPath);
    }

    _texts[idText].setFont(_fonts[idFont]);
    _texts[idText].setString(text);
    _texts[idText].setCharacterSize(size);
    _texts[idText].setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    return idText;
}

void SfmlGraphic::updateText(size_t id, std::string text, int size, RColor color)
{
    if (_texts.find(id) == _texts.end())
        return;
    _texts[id].setString(text);
    _texts[id].setCharacterSize(size);
    _texts[id].setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

void SfmlGraphic::setTextPosition(float x, float y, size_t id)
{
    if (_texts.find(id) == _texts.end())
        return;
    _texts[id].setPosition(x, y);
}

EXPORT_API IGraphic *createGraphic()
{
    return new SfmlGraphic();
}