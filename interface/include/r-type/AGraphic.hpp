/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AGraphic
*/

#pragma once

#include <r-type/IGraphic.hpp>

class AGraphic: virtual public IGraphic {
    public:
        /**
         * @class AGraphic
         * @brief A base class for graphical components in the R-Type game.
         *
         * This class serves as an abstract base class for all graphical components
         * in the R-Type game. It inherits from the IGraphic interface.
         */
        AGraphic(): IGraphic(){};

        /**
         * @brief Virtual destructor for the AGraphic class.
         *
         * This destructor is declared as default, meaning it will use the compiler-generated
         * default implementation. It ensures that derived classes can be properly cleaned up
         * when an object of AGraphic or its derived class is deleted.
         */
        virtual ~AGraphic() = default;

        /**
         * @brief Creates a window with the specified dimensions and name.
         *
         * This pure virtual function must be implemented by derived classes to
         * create a graphical window.
         *
         * @param x The width of the window.
         * @param y The height of the window.
         * @param name The title of the window.
         */
        virtual void createWindow(int x, int y, std::string name) = 0;

        /**
         * @brief Pure virtual function to create a sprite.
         *
         * This function is intended to be overridden by derived classes to handle the
         * creation of a sprite. The implementation should return a unique identifier
         * for the created sprite.
         *
         * @return size_t A unique identifier for the created sprite.
         */
        virtual size_t createSprite() = 0;

        /**
         * @brief Creates a texture from the given file path.
         *
         * This function takes a file path as a string and creates a texture from the file located at that path.
         * The function is pure virtual and must be implemented by derived classes.
         *
         * @param path The file path to the texture file.
         * @return A size_t representing the ID or handle of the created texture.
         */
        virtual size_t createTexture(std::string path) = 0;

        /**
         * @brief Creates a rectangle shape with the specified dimensions.
         *
         * This pure virtual function must be implemented by derived classes to create
         * a rectangle shape with the given width and height.
         *
         * @param x The width of the rectangle.
         * @param y The height of the rectangle.
         * @return A size_t value representing the identifier or handle of the created rectangle shape.
         */
        virtual size_t createRectangleShape(float x, float y) = 0;

        /**
         * @brief Sets the texture for a given sprite.
         *
         * This function assigns a texture to a sprite identified by their respective IDs.
         *
         * @param spriteId The ID of the sprite to which the texture will be applied.
         * @param textureId The ID of the texture to be applied to the sprite.
         */
        virtual void setSpriteTexture(size_t spriteId, size_t textureId) = 0;

        /**
         * @brief Set the position of a sprite.
         *
         * This pure virtual function sets the position of a sprite identified by its ID.
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
         * @brief Set the rotation angle of the sprite with the given ID.
         *
         * @param angle The rotation angle in degrees.
         * @param id The unique identifier of the sprite to be rotated.
         */
        virtual void setSpriteRotation(float angle, size_t id) = 0;

        /**
         * @brief Sets the position of a rectangle shape.
         *
         * This pure virtual function sets the position of a rectangle shape identified by the given ID.
         *
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         * @param id The identifier of the rectangle shape to be moved.
         */
        virtual void setRectangleShapePosition(float x, float y, size_t id) = 0;

        /**
         * @brief Sets the size of the rectangle shape.
         *
         * This pure virtual function sets the width and height of the rectangle shape
         * identified by the given ID.
         *
         * @param x The width of the rectangle shape.
         * @param y The height of the rectangle shape.
         * @param id The identifier of the rectangle shape to be resized.
         */
        virtual void setRectangleShapeSize(float x, float y, size_t id) = 0;

        /**
         * @brief Sets the rotation angle of a rectangle shape.
         *
         * This pure virtual function sets the rotation angle of a rectangle shape identified by the given ID.
         *
         * @param angle The rotation angle in degrees.
         * @param id The unique identifier of the rectangle shape.
         */
        virtual void setRectangleShapeRotation(float angle, size_t id) = 0;

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
         * @param id The identifier of the rectangle shape to be colored.
         */
        virtual void setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) = 0;

        /**
         * @brief Get the size of the texture.
         *
         * This function retrieves the dimensions of a texture identified by the given ID.
         *
         * @param id The identifier of the texture.
         * @return A pair of floats representing the width and height of the texture.
         */
        virtual std::pair<float, float> getTextureSize(size_t id) = 0;

        /**
         * @brief Draws a sprite with the given identifier.
         *
         * This pure virtual function must be implemented by derived classes to handle
         * the drawing of a sprite identified by the provided ID.
         *
         * @param id The unique identifier of the sprite to be drawn.
         */
        virtual void drawSprite(size_t id) = 0;

        /**
         * @brief Draws a rectangle shape with the specified identifier.
         *
         * This pure virtual function must be implemented by derived classes to
         * handle the drawing of a rectangle shape identified by the given ID.
         *
         * @param id The unique identifier of the rectangle shape to be drawn.
         */
        virtual void drawRectangleShape(size_t id) = 0;

        /**
         * @brief Draws text on the screen.
         *
         * This pure virtual function is responsible for drawing text identified by the given ID.
         * Implementations of this function should handle the rendering of text based on the provided ID.
         *
         * @param id The unique identifier of the text to be drawn.
         */
        virtual void drawText(size_t id) = 0;

        /**
         * @brief Pure virtual function to handle events.
         *
         * This function must be overridden by any derived class to provide
         * specific event handling logic.
         */
        virtual void eventHandler() = 0;

        /**
         * @brief Checks if a specific key on the keyboard is currently pressed.
         *
         * @param key The key to check for its pressed state.
         * @return true if the specified key is pressed, false otherwise.
         */
        virtual bool isKeyPressed(KeyBoard key) = 0;

        /**
         * @brief Pure virtual function to get the key pressed.
         *
         * This function should be implemented by derived classes to return the key that is currently pressed.
         *
         * @return KeyBoard The key that is currently pressed.
         */
        virtual KeyBoard getKeyPressed() = 0;

        /**
         * @brief Checks if the mouse button is currently pressed.
         *
         * This pure virtual function should be overridden by derived classes to
         * provide the specific implementation for detecting mouse button press state.
         *
         * @return true if the mouse button is pressed, false otherwise.
         */
        virtual bool isMousePressed() = 0;

        /**
         * @brief Get the current position of the mouse cursor.
         *
         * This function returns the current position of the mouse cursor as a pair of
         * floating-point values, where the first element represents the x-coordinate
         * and the second element represents the y-coordinate.
         *
         * @return std::pair<float, float> A pair containing the x and y coordinates of the mouse cursor.
         */
        virtual std::pair<float, float> getMousePosition() = 0;

        /**
         * @brief Pure virtual function to display the window.
         *
         * This function must be overridden by any derived class to handle the
         * display logic for the window. It is called to render the contents
         * of the window.
         */
        virtual void windowDisplay() = 0;

        /**
         * @brief Clears the window.
         *
         * This pure virtual function is intended to be overridden by derived classes
         * to implement the functionality for clearing the window. This typically
         * involves resetting the window's contents to a default state, such as
         * filling it with a background color.
         */
        virtual void windowClear() = 0;

        /**
         * @brief Pure virtual function to handle the closing of the window.
         *
         * This function should be overridden by derived classes to implement
         * specific behavior when the window is requested to close.
         */
        virtual void windowClose() = 0;

        /**
         * @brief Creates a text object with the specified properties.
         *
         * @param text The string of text to be displayed.
         * @param fontPath The file path to the font to be used.
         * @param size The size of the text.
         * @param color The color of the text.
         * @return A unique identifier for the created text object.
         */
        virtual size_t createText(std::string text, std::string fontPath, int size, RColor color) = 0;

        /**
         * @brief Set the position of the text with the specified ID.
         *
         * @param x The x-coordinate of the text position.
         * @param y The y-coordinate of the text position.
         * @param id The identifier of the text to be positioned.
         */
        virtual void setTextPosition(float x, float y, size_t id) = 0;

        /**
         * @brief Updates the text of a graphical element.
         *
         * This function updates the text content, size, and color of a graphical element identified by the given ID.
         *
         * @param id The unique identifier of the graphical element to be updated.
         * @param text The new text content to be set for the graphical element.
         * @param size The new size of the text.
         * @param color The new color of the text, represented as an RColor object.
         */
        virtual void updateText(size_t id, std::string text, int size, RColor color) = 0;
    protected:
    private:
};