/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AGraphic.hpp>

class SfmlGraphic : virtual public AGraphic {
    public:
        /**
         * @class SfmlGraphic
         * @brief A class responsible for handling graphical operations using SFML.
         *
         * This class provides functionalities to manage and render graphics using the
         * Simple and Fast Multimedia Library (SFML). It encapsulates the necessary
         * operations to initialize, update, and display graphical content.
         */
        SfmlGraphic();

        /**
         * @brief Destructor for the SfmlGraphic class.
         *
         * This destructor is responsible for cleaning up any resources
         * that the SfmlGraphic class may have allocated during its lifetime.
         */
        ~SfmlGraphic();

        /**
         * @brief Creates a window with the specified dimensions and name.
         *
         * @param x The width of the window.
         * @param y The height of the window.
         * @param name The title of the window.
         */
        void createWindow(int x, int y, std::string name) override;

        /**
         * @brief Creates a new sprite and returns its unique identifier.
         *
         * This function overrides the base class implementation to create a sprite
         * using the SFML library. The sprite is added to the internal collection
         * and a unique identifier is returned to the caller.
         *
         * @return size_t The unique identifier of the created sprite.
         */
        size_t createSprite() override;

        /**
         * @brief Creates a texture from the specified file path.
         *
         * This function loads an image from the given file path and creates a texture
         * that can be used for rendering. The texture is identified by a unique size_t
         * identifier which is returned by this function.
         *
         * @param path The file path to the image to be loaded as a texture.
         * @return A size_t identifier for the created texture.
         */
        size_t createTexture(std::string path) override;

        /**
         * @brief Creates a rectangle shape with the specified dimensions.
         *
         * @param x The width of the rectangle.
         * @param y The height of the rectangle.
         * @return size_t An identifier for the created rectangle shape.
         */
        size_t createRectangleShape(float x, float y) override;

        /**
         * @brief Sets the texture of a sprite.
         *
         * This function assigns a texture to a sprite identified by the given sprite ID.
         *
         * @param spriteId The ID of the sprite to which the texture will be applied.
         * @param textureId The ID of the texture to be applied to the sprite.
         */
        void setSpriteTexture(size_t spriteId, size_t textureId) override;

        /**
         * @brief Sets the position of the sprite with the given ID.
         *
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         * @param id The unique identifier of the sprite to be moved.
         */
        void setSpritePosition(float x, float y, size_t id) override;

        /**
         * @brief Sets the scale of the sprite with the given ID.
         *
         * This function adjusts the scale of the sprite identified by the specified ID.
         * The scaling factors for the x and y axes are provided as parameters.
         *
         * @param x The scaling factor for the x-axis.
         * @param y The scaling factor for the y-axis.
         * @param id The unique identifier of the sprite to be scaled.
         */
        void setSpriteScale(float x, float y, size_t id) override;

        /**
         * @brief Sets the rotation angle of the sprite with the given ID.
         *
         * @param angle The rotation angle in degrees.
         * @param id The unique identifier of the sprite to be rotated.
         */
        void setSpriteRotation(float angle, size_t id) override;

        /**
         * @brief Sets the position of a rectangle shape.
         *
         * This function sets the position of the rectangle shape identified by the given ID.
         *
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         * @param id The identifier of the rectangle shape to be moved.
         */
        void setRectangleShapePosition(float x, float y, size_t id) override;

        /**
         * @brief Sets the size of a rectangle shape.
         *
         * This function sets the width and height of a rectangle shape identified by the given ID.
         *
         * @param x The width of the rectangle shape.
         * @param y The height of the rectangle shape.
         * @param id The identifier of the rectangle shape to be resized.
         */
        void setRectangleShapeSize(float x, float y, size_t id) override;

        /**
         * @brief Sets the rotation angle of a rectangle shape identified by its ID.
         *
         * @param angle The rotation angle in degrees.
         * @param id The unique identifier of the rectangle shape to be rotated.
         */
        void setRectangleShapeRotation(float angle, size_t id) override;

        /**
         * @brief Sets the fill color of a rectangle shape.
         *
         * This function sets the fill color of a rectangle shape identified by the given ID.
         * The color is specified using RGBA values.
         *
         * @param r The red component of the color (0-255).
         * @param g The green component of the color (0-255).
         * @param b The blue component of the color (0-255).
         * @param a The alpha (transparency) component of the color (0-255).
         * @param id The identifier of the rectangle shape to be modified.
         */
        void setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) override;

        /**
         * @brief Retrieves the size of the texture associated with the given ID.
         *
         * @param id The identifier of the texture.
         * @return A std::pair<float, float> where the first element is the width and the second element is the height of the texture.
         */
        std::pair<float, float> getTextureSize(size_t id) override;

        /**
         * @brief Draws a sprite with the given ID.
         *
         * This function overrides the base class method to draw a sprite
         * identified by the specified ID. The sprite is rendered using
         * the SFML graphics library.
         *
         * @param id The unique identifier of the sprite to be drawn.
         */
        void drawSprite(size_t id) override;

        /**
         * @brief Draws a rectangle shape with the specified ID.
         *
         * This function overrides the base class method to draw a rectangle shape
         * identified by the given ID. The ID corresponds to a specific rectangle
         * shape that has been previously defined or loaded.
         *
         * @param id The unique identifier of the rectangle shape to be drawn.
         */
        void drawRectangleShape(size_t id) override;

        /**
         * @brief Draws text on the screen.
         *
         * This function draws the text associated with the given identifier.
         *
         * @param id The identifier of the text to be drawn.
         */
        void drawText(size_t id) override;

        /**
         * @brief Handles events for the graphical interface.
         *
         * This function is responsible for processing and handling
         * various events such as user inputs, window events, etc.
         * It overrides the base class event handler to provide
         * specific functionality for the SFML graphics implementation.
         */
        void eventHandler() override;

        /**
         * @brief Checks if a specific key is currently pressed.
         *
         * @param key The key to check.
         * @return true if the key is pressed, false otherwise.
         */
        bool isKeyPressed(KeyBoard key) override;

        /**
         * @brief Checks if the mouse button is currently pressed.
         *
         * This function overrides the base class implementation to provide
         * specific functionality for detecting mouse button presses.
         *
         * @return true if the mouse button is pressed, false otherwise.
         */
        bool isMousePressed() override;

        /**
         * @brief Gets the key that is currently pressed.
         *
         * This function returns the key that is currently pressed.
         *
         * @return KeyBoard The key that is currently pressed.
         */
        KeyBoard getKeyPressed() override;

        /**
         * @brief Get the current position of the mouse cursor.
         *
         * This function returns the current position of the mouse cursor
         * as a pair of floating-point values representing the x and y coordinates.
         *
         * @return std::pair<float, float> A pair containing the x and y coordinates of the mouse cursor.
         */
        std::pair<float, float> getMousePosition() override;

        /**
         * @brief Displays the contents of the window.
         *
         * This function is responsible for rendering the current frame to the window.
         * It should be called once per frame to update the display with the latest
         * rendered content.
         */
        void windowDisplay() override;

        /**
         * @brief Clears the window with the current clear color.
         *
         * This function clears the entire window with the color specified by the
         * current clear color. It is typically called at the beginning of the
         * rendering loop to prepare the window for drawing.
         */
        void windowClear() override;

        /**
         * @brief Closes the window.
         *
         * This function is responsible for closing the window and performing any necessary cleanup operations.
         */
        void windowClose() override;

        /**
         * @brief Creates a text object with the specified properties.
         *
         * @param text The string to be displayed.
         * @param fontPath The file path to the font to be used.
         * @param size The size of the text.
         * @param color The color of the text.
         * @return A size_t identifier for the created text object.
         */
        size_t createText(std::string text, std::string fontPath, int size, RColor color) override;

        /**
         * @brief Sets the position of the text with the specified ID.
         *
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         * @param id The identifier of the text to be moved.
         */
        void setTextPosition(float x, float y, size_t id) override;

        /**
         * @brief Updates the text properties of a graphical element.
         *
         * @param id The unique identifier of the text element to update.
         * @param text The new text string to display.
         * @param size The new font size of the text.
         * @param color The new color of the text, represented as an RColor object.
         */
        void updateText(size_t id, std::string text, int size, RColor color) override;

    protected:
    private:
        /**
         * @brief A window that can be used for rendering 2D graphics.
         *
         * sf::RenderWindow is a class provided by the SFML library that represents a window
         * that can be used for drawing 2D graphics. It inherits from both sf::Window and
         * sf::RenderTarget, combining the features of a window and a rendering target.
         *
         * The window can be created with a specific size and title, and it provides functions
         * to handle events, control the frame rate, and manage the rendering loop.
         *
         * Example usage:
         * ```
         * sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
         * while (window.isOpen()) {
         *     sf::Event event;
         *     while (window.pollEvent(event)) {
         *         if (event.type == sf::Event::Closed)
         *             window.close();
         *     }
         *     window.clear();
         *     // Draw your graphics here
         *     window.display();
         * }
         * ```
         *
         * @see sf::Window
         * @see sf::RenderTarget
         */
        sf::RenderWindow _window;

        /**
         * @brief Holds all the events that SFML can handle.
         *
         * This class encapsulates all the possible events that can be received
         * from the windowing system. It includes events such as keyboard input,
         * mouse movement, window resizing, and more.
         */
        sf::Event _event;

        /**
         * @brief A map that associates unique identifiers with SFML sprites.
         *
         * This unordered map uses a size_t as the key to uniquely identify each sprite,
         * and stores the corresponding sf::Sprite object as the value. It allows for
         * efficient retrieval and management of sprites based on their unique identifiers.
         */
        std::unordered_map<size_t, sf::Sprite> _sprites;

        /**
         * @brief A map that associates a unique identifier with an SFML texture.
         *
         * This unordered map uses a size_t as the key to uniquely identify each texture,
         * and an sf::Texture as the value to store the texture data. It allows for efficient
         * retrieval and management of textures by their unique identifiers.
         */
        std::unordered_map<size_t, sf::Texture> _textures;

        /**
         * @brief A hash table that maps unique identifiers to SFML Text objects.
         *
         * This unordered map uses size_t as the key type, which typically represents
         * unique identifiers for the text objects. The values are sf::Text objects
         * from the SFML library, which are used for rendering text in a graphical
         * application.
         */
        std::unordered_map<size_t, sf::Text> _texts;

        /**
         * @brief A map that associates unique identifiers with sf::RectangleShape objects.
         *
         * This unordered map uses size_t as the key type and sf::RectangleShape as the value type.
         * It allows for efficient retrieval and storage of rectangle shapes based on their unique identifiers.
         */
        std::unordered_map<size_t, sf::RectangleShape> _rectangleShapes;

        /**
         * @brief A map that associates a unique identifier with an sf::Font object.
         *
         * This unordered map uses a size_t as the key to uniquely identify each sf::Font object.
         * It allows for efficient retrieval and management of font resources within the application.
         */
        std::unordered_map<size_t, sf::Font> _fonts;
};
