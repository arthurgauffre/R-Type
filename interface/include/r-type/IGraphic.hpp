/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IGraphic
*/

#pragma once

#ifdef _WIN32
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C"
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include <r-type/Enum.hpp>
#include <graphics/Color.hpp>

class IGraphic {
    public:
        /**
         * @class IGraphic
         * @brief Interface for graphical operations.
         *
         * This class provides an interface for graphical operations that can be
         * implemented by different graphical systems.
         */
        IGraphic(){};
        /**
         * @brief Virtual destructor for the IGraphic interface.
         *
         * This ensures that derived classes can clean up resources properly when an object is deleted through a pointer to IGraphic.
         */
        virtual ~IGraphic() = default;

        /**
         * @brief Creates a window with the specified dimensions and name.
         *
         * This pure virtual function must be implemented by any class that
         * inherits from this interface. It is responsible for creating a
         * graphical window with the given width, height, and title.
         *
         * @param x The width of the window.
         * @param y The height of the window.
         * @param name The title of the window.
         */
        virtual void createWindow(int x, int y, std::string name) = 0;

        /**
         * @brief Creates a new sprite.
         *
         * This pure virtual function is intended to be overridden by derived classes
         * to create and return a new sprite. The function returns a unique identifier
         * for the created sprite.
         *
         * @return size_t A unique identifier for the created sprite.
         */
        virtual size_t createSprite() = 0;

        /**
         * @brief Creates a texture from the specified file path.
         *
         * This function loads an image from the given file path and creates a texture
         * that can be used for rendering. The texture is identified by a unique ID
         * which is returned by this function.
         *
         * @param path The file path to the image to be loaded as a texture.
         * @return A unique ID representing the created texture.
         */
        virtual size_t createTexture(std::string path) = 0;

        /**
         * @brief Creates a rectangle shape with the specified dimensions.
         *
         * @param x The width of the rectangle.
         * @param y The height of the rectangle.
         * @return A size_t identifier for the created rectangle shape.
         */
        virtual size_t createRectangleShape(float x, float y) = 0;

        /**
         * @brief Sets the texture of a sprite.
         *
         * This function assigns a texture to a sprite identified by the given sprite ID.
         *
         * @param spriteId The ID of the sprite to which the texture will be assigned.
         * @param textureId The ID of the texture to be assigned to the sprite.
         */
        virtual void setSpriteTexture(size_t spriteId, size_t textureId) = 0;

        /**
         * @brief Set the position of a sprite.
         *
         * @param x The x-coordinate of the sprite's new position.
         * @param y The y-coordinate of the sprite's new position.
         * @param id The unique identifier of the sprite to be moved.
         */
        virtual void setSpritePosition(float x, float y, size_t id) = 0;

        /**
         * @brief Sets the scale of the sprite with the given ID.
         *
         * @param x The scale factor along the x-axis.
         * @param y The scale factor along the y-axis.
         * @param id The unique identifier of the sprite to be scaled.
         */
        virtual void setSpriteScale(float x, float y, size_t id) = 0;

        /**
         * @brief Set the rotation angle of a sprite.
         *
         * This function sets the rotation angle for the sprite identified by the given ID.
         *
         * @param angle The rotation angle in degrees.
         * @param id The unique identifier of the sprite to be rotated.
         */
        virtual void setSpriteRotation(float angle, size_t id) = 0;

        /**
         * @brief Set the position of a rectangle shape.
         *
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         * @param id The identifier of the rectangle shape to be moved.
         */
        virtual void setRectangleShapePosition(float x, float y, size_t id) = 0;

        /**
         * @brief Set the size of a rectangle shape.
         *
         * This function sets the width and height of a rectangle shape identified by the given ID.
         *
         * @param x The width of the rectangle shape.
         * @param y The height of the rectangle shape.
         * @param id The identifier of the rectangle shape to be resized.
         */
        virtual void setRectangleShapeSize(float x, float y, size_t id) = 0;

        /**
         * @brief Sets the rotation angle of a rectangle shape identified by the given ID.
         *
         * @param angle The rotation angle in degrees.
         * @param id The unique identifier of the rectangle shape to be rotated.
         */
        virtual void setRectangleShapeRotation(float angle, size_t id) = 0;

        /**
         * @brief Sets the fill color of a rectangle shape.
         *
         * @param r The red component of the color (0-255).
         * @param g The green component of the color (0-255).
         * @param b The blue component of the color (0-255).
         * @param a The alpha component of the color (0-255).
         * @param id The identifier of the rectangle shape to be modified.
         */
        virtual void setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) = 0;

        /**
         * @brief Retrieves the size of the texture associated with the given ID.
         *
         * @param id The identifier of the texture.
         * @return A pair of floats representing the width and height of the texture.
         */
        virtual std::pair<float, float> getTextureSize(size_t id) = 0;

        /**
         * @brief Draws a sprite with the given identifier.
         *
         * This function is responsible for rendering a sprite on the screen
         * based on the provided sprite ID. The sprite ID corresponds to a
         * specific sprite resource that has been previously loaded.
         *
         * @param id The identifier of the sprite to be drawn.
         */
        virtual void drawSprite(size_t id) = 0;

        /**
         * @brief Draws a rectangle shape with the specified identifier.
         *
         * This function is responsible for rendering a rectangle shape
         * on the screen. The shape is identified by a unique identifier
         * which is passed as a parameter.
         *
         * @param id The unique identifier of the rectangle shape to be drawn.
         */
        virtual void drawRectangleShape(size_t id) = 0;

        /**
         * @brief Draws text on the screen.
         *
         * This function is responsible for rendering text identified by the given ID.
         *
         * @param id The unique identifier for the text to be drawn.
         */
        virtual void drawText(size_t id) = 0;

        /**
         * @brief Handles events for the graphical interface.
         *
         * This pure virtual function must be implemented by any class that
         * inherits from IGraphic. It is responsible for processing and
         * handling events such as user input or system messages.
         */
        virtual void eventHandler() = 0;

        /**
         * @brief Checks if a specific key on the keyboard is currently pressed.
         *
         * @param key The key to check, represented by the KeyBoard enum.
         * @return true if the specified key is pressed, false otherwise.
         */
        virtual bool isKeyPressed(KeyBoard key) = 0;

        /**
         * @brief Checks if the mouse button is currently pressed.
         *
         * This function should be implemented to determine whether any mouse button
         * is being pressed at the moment of the call.
         *
         * @return true if a mouse button is pressed, false otherwise.
         */
        virtual bool isMousePressed() = 0;

        /**
         * @brief Get the current position of the mouse cursor.
         *
         * @return A std::pair containing the x and y coordinates of the mouse cursor.
         */
        virtual std::pair<float, float> getMousePosition() = 0;

        /**
         * @brief Displays the window.
         *
         * This pure virtual function is responsible for displaying the window.
         * Implementations of this interface must provide the specific details
         * of how the window is displayed.
         */
        virtual void windowDisplay() = 0;

        /**
         * @brief Clears the window.
         *
         * This function is responsible for clearing the window, typically by filling it with a background color.
         * It should be called before drawing any new frame to ensure that the previous frame's contents are not visible.
         */
        virtual void windowClear() = 0;

        /**
         * @brief Closes the window.
         *
         * This pure virtual function should be implemented to handle the logic for closing the window.
         */
        virtual void windowClose() = 0;

        /**
         * @brief Creates a text object with the specified properties.
         *
         * @param text The string content of the text object.
         * @param fontPath The file path to the font to be used.
         * @param size The size of the text.
         * @param color The color of the text.
         * @return A unique identifier for the created text object.
         */
        virtual size_t createText(std::string text, std::string fontPath, int size, RColor color) = 0;

        /**
         * @brief Sets the position of the text with the specified ID.
         *
         * @param x The x-coordinate of the text position.
         * @param y The y-coordinate of the text position.
         * @param id The identifier of the text to be positioned.
         */
        virtual void setTextPosition(float x, float y, size_t id) = 0;

        /**
         * @brief Updates the text properties of a graphical element.
         *
         * @param id The unique identifier of the text element to be updated.
         * @param text The new text string to be displayed.
         * @param size The new font size of the text.
         * @param color The new color of the text, represented as an RColor object.
         */
        virtual void updateText(size_t id, std::string text, int size, RColor color) = 0;

    protected:
        /**
         * @brief A vector that stores sprite IDs.
         *
         * This vector holds the IDs of the sprites used in the graphical interface.
         * Each element in the vector is of type size_t, representing a unique identifier for a sprite.
         */
        std::vector<size_t> _spritesId;

        /**
         * @brief A vector that stores text identifiers.
         *
         * This vector holds the IDs of texts, which are represented as size_t values.
         * It is used to manage and reference different text elements within the system.
         */
        std::vector<size_t> _textsId;

        /**
         * @brief A map that associates texture names with their corresponding IDs.
         *
         * This unordered map uses texture names as keys (std::string) and their
         * corresponding unique identifiers (size_t) as values. It allows for
         * efficient retrieval of texture IDs based on their names.
         */
        std::unordered_map<std::string, size_t> _texturesId;

        /**
         * @brief A map that associates font names with their corresponding IDs.
         *
         * This unordered map stores font identifiers where the key is a string representing
         * the font name and the value is a size_t representing the unique ID of the font.
         */
        std::unordered_map<std::string, size_t> _fontsId;

        /**
         * @brief A vector that stores the IDs of rectangle shapes.
         *
         * This vector holds the unique identifiers (IDs) for rectangle shapes
         * used within the graphical interface. Each ID is of type `size_t`.
         */
        std::vector<size_t> _rectangleShapesId;
    private:

};
