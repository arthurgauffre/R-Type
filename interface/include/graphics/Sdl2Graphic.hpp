/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sdl2Graphic
*/

#ifndef SDL2GRAPHIC_H
#define SDL2GRAPHIC_H

#include <r-type/AGraphic.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <utility>

class Sdl2Graphic : public AGraphic {
public:
    Sdl2Graphic();
    ~Sdl2Graphic();

    void createWindow(int x, int y, std::string name) override;
    size_t createSprite() override;
    size_t createTexture(std::string path) override;
    size_t createRectangleShape(float x, float y) override;
    void setSpriteTexture(size_t spriteId, size_t textureId) override;
    void setSpritePosition(float x, float y, size_t id) override;
    void setSpriteScale(float x, float y, size_t id) override;
    void setSpriteRotation(float angle, size_t id) override;
    void setSpriteColor(size_t id, RColor color) override;
    void setRectangleShapePosition(float x, float y, size_t id) override;
    void setRectangleShapeSize(float x, float y, size_t id) override;
    void setRectangleShapeRotation(float angle, size_t id) override;
    void setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) override;
    std::pair<float, float> getTextureSize(size_t id) override;
    void drawSprite(size_t id) override;
    void drawRectangleShape(size_t id) override;
    void drawText(size_t id) override;
    void eventHandler() override;
    bool isKeyPressed(KeyBoard key) override;
    bool isMousePressed() override;
    KeyBoard getKeyPressed() override;
    std::pair<float, float> getMousePosition() override;
    void windowDisplay() override;
    void windowClear() override;
    void windowClose() override;
    size_t createText(std::string text, std::string fontPath, int size, RColor color) override;
    void setTextPosition(float x, float y, size_t id) override;
    void updateText(size_t id, std::string text, int size, RColor color) override;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unordered_map<size_t, SDL_Texture*> textures;
    std::unordered_map<size_t, SDL_Rect> sprites;
    std::unordered_map<size_t, TTF_Font*> fonts;
    size_t nextId;

    void handleError(const std::string& msg);
};

#endif // SDL2GRAPHIC_H
