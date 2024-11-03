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

/**
 * @brief Creates a new SFML window with the specified dimensions and title.
 * 
 * @param x The width of the window in pixels.
 * @param y The height of the window in pixels.
 * @param name The title of the window.
 */
void SfmlGraphic::createWindow(int x, int y, std::string name)
{
    _window.create(sf::VideoMode(x, y), name);
}

/**
 * @brief Creates a new sprite and assigns it a unique ID.
 * 
 * This function generates a new sprite, assigns it a unique identifier,
 * and stores it in the internal sprite container. The ID is generated
 * based on the current size of the sprite ID container.
 * 
 * @return size_t The unique ID assigned to the newly created sprite.
 */
size_t SfmlGraphic::createSprite()
{
    size_t id = _spritesId.size();
    _spritesId.push_back(id);
    _sprites[id] = sf::Sprite();
    return id;
}

/**
 * @brief Creates a texture from the given file path and returns its unique identifier.
 *
 * This function checks if a texture with the specified path already exists. If it does,
 * the function returns the existing texture's identifier. Otherwise, it creates a new
 * texture, assigns it a unique identifier, and loads the texture from the file.
 *
 * @param path The file path to the texture to be loaded.
 * @return The unique identifier of the texture.
 */
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

/**
 * @brief Creates a rectangle shape with the specified dimensions.
 *
 * This function creates a new rectangle shape with the given width and height,
 * assigns it a unique identifier, and stores it in the internal collection.
 *
 * @param x The width of the rectangle shape.
 * @param y The height of the rectangle shape.
 * @return The unique identifier of the created rectangle shape.
 */
size_t SfmlGraphic::createRectangleShape(float x, float y)
{
    size_t id = _rectangleShapesId.size();
    _rectangleShapesId.push_back(id);
    _rectangleShapes[id] = sf::RectangleShape();
    _rectangleShapes[id].setSize(sf::Vector2f(x, y));
    return id;
}

/**
 * @brief Sets the texture of a sprite.
 * 
 * This function assigns a texture to a sprite identified by their respective IDs.
 * 
 * @param spriteId The ID of the sprite to which the texture will be assigned.
 * @param textureId The ID of the texture to be assigned to the sprite.
 */
void SfmlGraphic::setSpriteTexture(size_t spriteId, size_t textureId)
{
    _sprites[spriteId].setTexture(_textures[textureId]);
}

/**
 * @brief Sets the position of the sprite with the given ID.
 * 
 * @param x The x-coordinate of the new position.
 * @param y The y-coordinate of the new position.
 * @param id The ID of the sprite to be moved.
 */
void SfmlGraphic::setSpritePosition(float x, float y, size_t id)
{
    _sprites[id].setPosition(x, y);
}

/**
 * @brief Sets the scale of the sprite with the given ID.
 * 
 * This function modifies the scale of the sprite identified by the provided ID.
 * The scale is set using the specified x and y values.
 * 
 * @param x The scale factor along the x-axis.
 * @param y The scale factor along the y-axis.
 * @param id The identifier of the sprite to be scaled.
 */
void SfmlGraphic::setSpriteScale(float x, float y, size_t id)
{
    _sprites[id].setScale(x, y);
}

/**
 * @brief Sets the rotation angle of the sprite with the given ID.
 * 
 * @param angle The rotation angle in degrees.
 * @param id The ID of the sprite to be rotated.
 */
void SfmlGraphic::setSpriteRotation(float angle, size_t id)
{
    _sprites[id].setRotation(angle);
}

/**
 * @brief Sets the color of the sprite with the given ID.
 * 
 * This function changes the color of the sprite identified by the specified ID.
 * The color is set using the provided RColor object, which contains the RGBA values.
 * 
 * @param id The ID of the sprite to be colored.
 * @param color The RColor object containing the RGBA values to set the sprite's color.
 */
void SfmlGraphic::setSpriteColor(size_t id, RColor color)
{
    _sprites[id].setColor(sf::Color(color.r, color.g, color.b, color.a));
}

/**
 * @brief Sets the position of a rectangle shape.
 * 
 * This function sets the position of the rectangle shape identified by the given ID.
 * 
 * @param x The x-coordinate of the new position.
 * @param y The y-coordinate of the new position.
 * @param id The identifier of the rectangle shape to be moved.
 */
void SfmlGraphic::setRectangleShapePosition(float x, float y, size_t id)
{
    _rectangleShapes[id].setPosition(x, y);
}

/**
 * @brief Sets the size of a rectangle shape.
 * 
 * This function sets the size of the rectangle shape identified by the given ID.
 * 
 * @param x The width of the rectangle shape.
 * @param y The height of the rectangle shape.
 * @param id The identifier of the rectangle shape to be resized.
 */
void SfmlGraphic::setRectangleShapeSize(float x, float y, size_t id)
{
    _rectangleShapes[id].setSize(sf::Vector2f(x, y));
}

/**
 * @brief Sets the rotation angle of a rectangle shape.
 *
 * This function sets the rotation angle of the rectangle shape identified by the given ID.
 *
 * @param angle The rotation angle to set, in degrees.
 * @param id The identifier of the rectangle shape to rotate.
 */
void SfmlGraphic::setRectangleShapeRotation(float angle, size_t id)
{
    _rectangleShapes[id].setRotation(angle);
}

/**
 * @brief Sets the fill color of a rectangle shape.
 * 
 * This function sets the fill color of the rectangle shape identified by the given ID.
 * The color is specified by the RGBA values provided as parameters.
 * 
 * @param r The red component of the color (0-255).
 * @param g The green component of the color (0-255).
 * @param b The blue component of the color (0-255).
 * @param a The alpha (transparency) component of the color (0-255).
 * @param id The identifier of the rectangle shape to be modified.
 */
void SfmlGraphic::setRectangleShapeFillColor(int r, int g, int b, int a, size_t id)
{
    _rectangleShapes[id].setFillColor(sf::Color(r, g, b, a));
}

/**
 * @brief Retrieves the size of the texture with the specified ID.
 * 
 * @param id The ID of the texture whose size is to be retrieved.
 * @return A std::pair<float, float> containing the width (first) and height (second) of the texture.
 */
std::pair<float, float> SfmlGraphic::getTextureSize(size_t id)
{
    return std::make_pair(_textures[id].getSize().x, _textures[id].getSize().y);
}

/**
 * @brief Draws a sprite on the window.
 * 
 * This function draws the sprite associated with the given ID on the window.
 * 
 * @param id The ID of the sprite to be drawn.
 */
void SfmlGraphic::drawSprite(size_t id)
{
    _window.draw(_sprites[id]);
}

/**
 * @brief Draws a rectangle shape on the window.
 * 
 * This function draws a rectangle shape identified by the given ID
 * from the _rectangleShapes container onto the window.
 * 
 * @param id The identifier of the rectangle shape to be drawn.
 */
void SfmlGraphic::drawRectangleShape(size_t id)
{
    _window.draw(_rectangleShapes[id]);
}

/**
 * @brief Draws a text object on the window.
 * 
 * This function draws a text object identified by the given ID on the window.
 * The text object must have been previously created and stored in the _texts container.
 * 
 * @param id The identifier of the text object to be drawn.
 */
void SfmlGraphic::drawText(size_t id)
{
    _window.draw(_texts[id]);
}

/**
 * @brief Handles SFML window events.
 *
 * This function processes all pending events for the SFML window. If a close event
 * is detected, it closes the window.
 */
void SfmlGraphic::eventHandler()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
}

/**
 * @brief Checks if a specific keyboard key is currently being pressed.
 * 
 * This function maps the custom KeyBoard enum values to the corresponding
 * sf::Keyboard values and checks if the specified key is pressed using
 * the SFML library.
 * 
 * @param key The key to check, represented by the KeyBoard enum.
 * @return true if the specified key is currently pressed, false otherwise.
 */
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

/**
 * @brief Checks which key is currently pressed and returns the corresponding KeyBoard enum value.
 * 
 * This function iterates through a predefined set of keys (A-Z, Space, Escape) and checks if any of them
 * are currently pressed using the SFML library's sf::Keyboard::isKeyPressed function. If a key is pressed,
 * it returns the corresponding KeyBoard enum value. If no key is pressed, it returns KeyBoard::Unknown.
 * 
 * @return KeyBoard The enum value corresponding to the key that is currently pressed, or KeyBoard::Unknown if no key is pressed.
 */
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

/**
 * @brief Checks if the left mouse button is currently pressed.
 * 
 * This function uses the SFML library to determine if the left mouse button
 * is being pressed at the moment of the call.
 * 
 * @return true if the left mouse button is pressed, false otherwise.
 */
bool SfmlGraphic::isMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

/**
 * @brief Retrieves the current position of the mouse cursor relative to the window.
 * 
 * @return std::pair<float, float> A pair containing the x and y coordinates of the mouse cursor.
 */
std::pair<float, float> SfmlGraphic::getMousePosition()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
    return std::make_pair(mousePosition.x, mousePosition.y);
}

/**
 * @brief Displays the contents of the window.
 * 
 * This function updates the window with the contents that have been drawn
 * since the last call to display. It effectively swaps the buffers and
 * shows the rendered frame on the screen.
 */
void SfmlGraphic::windowDisplay()
{
    _window.display();
}

/**
 * @brief Clears the window with the current clear color.
 * 
 * This function clears the entire window with the color that was set
 * previously using the window's clear color. It is typically called
 * at the beginning of the rendering process to prepare the window
 * for drawing the next frame.
 */
void SfmlGraphic::windowClear()
{
    _window.clear();
}

/**
 * @brief Closes the SFML window.
 *
 * This function closes the window managed by the SfmlGraphic instance.
 * It should be called when the window needs to be closed, such as when
 * the application is exiting or when the user requests to close the window.
 */
void SfmlGraphic::windowClose()
{
    _window.close();
}

/**
 * @brief Creates a text object with the specified properties and returns its ID.
 *
 * This function creates a new text object using the provided string, font path, size, and color.
 * It assigns a unique ID to the text object and stores it in the internal data structures.
 * If the font specified by the font path is already loaded, it reuses the existing font.
 * Otherwise, it loads the font from the specified file path.
 *
 * @param text The string to be displayed as text.
 * @param fontPath The file path to the font to be used.
 * @param size The character size of the text.
 * @param color The color of the text, represented as an RColor object.
 * @return The unique ID assigned to the created text object.
 */
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

/**
 * @brief Updates the text properties of a specific text entity.
 * 
 * This function updates the string, character size, and fill color of a text entity
 * identified by the given ID. If the ID does not exist in the text map, the function
 * returns without making any changes.
 * 
 * @param id The unique identifier of the text entity to update.
 * @param text The new string to set for the text entity.
 * @param size The new character size to set for the text entity.
 * @param color The new color to set for the text entity, represented as an RColor object.
 */
void SfmlGraphic::updateText(size_t id, std::string text, int size, RColor color)
{
    if (_texts.find(id) == _texts.end())
        return;
    _texts[id].setString(text);
    _texts[id].setCharacterSize(size);
    _texts[id].setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

/**
 * @brief Sets the position of a text object identified by its ID.
 * 
 * This function sets the position of a text object to the specified
 * coordinates (x, y). If the text object with the given ID does not
 * exist, the function does nothing.
 * 
 * @param x The x-coordinate of the new position.
 * @param y The y-coordinate of the new position.
 * @param id The unique identifier of the text object.
 */
void SfmlGraphic::setTextPosition(float x, float y, size_t id)
{
    if (_texts.find(id) == _texts.end())
        return;
    _texts[id].setPosition(x, y);
}

/**
 * @brief Factory function to create an instance of SfmlGraphic.
 * 
 * This function is exported using the EXPORT_API macro, making it available
 * for use in other modules or applications. It creates and returns a new
 * instance of the SfmlGraphic class, which implements the IGraphic interface.
 * 
 * @return IGraphic* Pointer to the newly created SfmlGraphic instance.
 */
EXPORT_API IGraphic *createGraphic()
{
    return new SfmlGraphic();
}