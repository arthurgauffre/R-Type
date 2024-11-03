/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sdl2Graphic
*/

#include <graphics/Sdl2Graphic.hpp>
#include <iostream>

Sdl2Graphic::Sdl2Graphic() : window(nullptr), renderer(nullptr), nextId(1) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        handleError("SDL could not initialize");
        return;
    }

    if (TTF_Init() == -1) {
        handleError("SDL_ttf could not initialize");
        return;
    }
}

Sdl2Graphic::~Sdl2Graphic() {
    windowClose();
    TTF_Quit();
}

void Sdl2Graphic::createWindow(int x, int y, std::string name) {
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN);
    if (!window) {
        handleError("Window could not be created");
        return;
    }
}

size_t Sdl2Graphic::createSprite() {
    sprites[nextId] = { 0, 0, 0, 0 }; 
    return nextId++;
}

size_t Sdl2Graphic::createTexture(std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        handleError("Failed to load texture");
        return 0;
    }
    textures[nextId] = texture;
    return nextId++;
}

size_t Sdl2Graphic::createRectangleShape(float x, float y) {
    sprites[nextId] = { static_cast<int>(x), static_cast<int>(y), 0, 0 };
    return nextId++;
}

void Sdl2Graphic::setSpriteTexture(size_t spriteId, size_t textureId) {
    int textureWidth, textureHeight;
    
    if (sprites.find(spriteId) == sprites.end() || textures.find(textureId) == textures.end()) {
        handleError("Invalid spriteId or textureId");
        return;
    }

    SDL_Rect& sprite = sprites[spriteId];
    SDL_Texture* texture = textures[textureId];

    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    sprite.w = textureWidth;
    sprite.h = textureHeight;
    SDL_RenderCopy(renderer, texture, NULL, &sprite);
}

void Sdl2Graphic::setSpritePosition(float x, float y, size_t id) {
    sprites[id].x = static_cast<int>(x);
    sprites[id].y = static_cast<int>(y);
}

void Sdl2Graphic::setSpriteScale(float x, float y, size_t id) {
    sprites[id].w = static_cast<int>(x * sprites[id].w);
    sprites[id].h = static_cast<int>(y * sprites[id].h);
}

void Sdl2Graphic::setSpriteRotation(float angle, size_t id) {
    // Rotation can't be handled 
}

void Sdl2Graphic::setSpriteColor(size_t id, RColor color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &sprites[id]);
}

void Sdl2Graphic::setRectangleShapePosition(float x, float y, size_t id) {
    sprites[id].x = static_cast<int>(x);
    sprites[id].y = static_cast<int>(y);
}

void Sdl2Graphic::setRectangleShapeSize(float x, float y, size_t id) {
    sprites[id].w = static_cast<int>(x);
    sprites[id].h = static_cast<int>(y);
}

void Sdl2Graphic::setRectangleShapeRotation(float angle, size_t id) {
      // Rotation can't be handled 
}

void Sdl2Graphic::setRectangleShapeFillColor(int r, int g, int b, int a, size_t id) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

std::pair<float, float> Sdl2Graphic::getTextureSize(size_t id) {
    int w, h;
    SDL_QueryTexture(textures[id], nullptr, nullptr, &w, &h);
    return { static_cast<float>(w), static_cast<float>(h) };
}

void Sdl2Graphic::drawSprite(size_t id) {
    SDL_RenderCopy(renderer, textures[id], nullptr, &sprites[id]);
}

void Sdl2Graphic::drawRectangleShape(size_t id) {
    SDL_RenderFillRect(renderer, &sprites[id]);
}

void Sdl2Graphic::drawText(size_t id) {
    
    SDL_Texture* texture;
    SDL_Rect rect;

    if (textures.find(id) == textures.end()) {
        handleError("Invalid text ID");
        return;
    }
    texture = textures[id];
    rect = sprites[id];
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Sdl2Graphic::eventHandler() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            windowClose(); 
        }
}


bool Sdl2Graphic::isKeyPressed(KeyBoard key) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    switch (key) {
        case KeyBoard::A: return state[SDL_SCANCODE_A];
        case KeyBoard::B: return state[SDL_SCANCODE_B];
        case KeyBoard::C: return state[SDL_SCANCODE_C];
        case KeyBoard::D: return state[SDL_SCANCODE_D];
        case KeyBoard::E: return state[SDL_SCANCODE_E];
        case KeyBoard::F: return state[SDL_SCANCODE_F];
        case KeyBoard::G: return state[SDL_SCANCODE_G];
        case KeyBoard::H: return state[SDL_SCANCODE_H];
        case KeyBoard::I: return state[SDL_SCANCODE_I];
        case KeyBoard::J: return state[SDL_SCANCODE_J];
        case KeyBoard::K: return state[SDL_SCANCODE_K];
        case KeyBoard::L: return state[SDL_SCANCODE_L];
        case KeyBoard::M: return state[SDL_SCANCODE_M];
        case KeyBoard::N: return state[SDL_SCANCODE_N];
        case KeyBoard::O: return state[SDL_SCANCODE_O];
        case KeyBoard::P: return state[SDL_SCANCODE_P];
        case KeyBoard::Q: return state[SDL_SCANCODE_Q];
        case KeyBoard::R: return state[SDL_SCANCODE_R];
        case KeyBoard::S: return state[SDL_SCANCODE_S];
        case KeyBoard::T: return state[SDL_SCANCODE_T];
        case KeyBoard::U: return state[SDL_SCANCODE_U];
        case KeyBoard::V: return state[SDL_SCANCODE_V];
        case KeyBoard::W: return state[SDL_SCANCODE_W];
        case KeyBoard::X: return state[SDL_SCANCODE_X];
        case KeyBoard::Y: return state[SDL_SCANCODE_Y];
        case KeyBoard::Z: return state[SDL_SCANCODE_Z];
        case KeyBoard::Space: return state[SDL_SCANCODE_SPACE];
        case KeyBoard::escape: return state[SDL_SCANCODE_ESCAPE];
        default: return false;
    }
}

bool Sdl2Graphic::isMousePressed() {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

KeyBoard Sdl2Graphic::getKeyPressed() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_A]) return KeyBoard::A;
    if (state[SDL_SCANCODE_B]) return KeyBoard::B;
    if (state[SDL_SCANCODE_C]) return KeyBoard::C;
    if (state[SDL_SCANCODE_D]) return KeyBoard::D;
    if (state[SDL_SCANCODE_E]) return KeyBoard::E;
    if (state[SDL_SCANCODE_F]) return KeyBoard::F;
    if (state[SDL_SCANCODE_G]) return KeyBoard::G;
    if (state[SDL_SCANCODE_H]) return KeyBoard::H;
    if (state[SDL_SCANCODE_I]) return KeyBoard::I;
    if (state[SDL_SCANCODE_J]) return KeyBoard::J;
    if (state[SDL_SCANCODE_K]) return KeyBoard::K;
    if (state[SDL_SCANCODE_L]) return KeyBoard::L;
    if (state[SDL_SCANCODE_M]) return KeyBoard::M;
    if (state[SDL_SCANCODE_N]) return KeyBoard::N;
    if (state[SDL_SCANCODE_O]) return KeyBoard::O;
    if (state[SDL_SCANCODE_P]) return KeyBoard::P;
    if (state[SDL_SCANCODE_Q]) return KeyBoard::Q;
    if (state[SDL_SCANCODE_R]) return KeyBoard::R;
    if (state[SDL_SCANCODE_S]) return KeyBoard::S;
    if (state[SDL_SCANCODE_T]) return KeyBoard::T;
    if (state[SDL_SCANCODE_U]) return KeyBoard::U;
    if (state[SDL_SCANCODE_V]) return KeyBoard::V;
    if (state[SDL_SCANCODE_W]) return KeyBoard::W;
    if (state[SDL_SCANCODE_X]) return KeyBoard::X;
    if (state[SDL_SCANCODE_Y]) return KeyBoard::Y;
    if (state[SDL_SCANCODE_Z]) return KeyBoard::Z;
    if (state[SDL_SCANCODE_SPACE]) return KeyBoard::Space;
    if (state[SDL_SCANCODE_ESCAPE]) return KeyBoard::escape;

    return KeyBoard::Unknown;
}

std::pair<float, float> Sdl2Graphic::getMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}

void Sdl2Graphic::windowDisplay() {
    SDL_RenderPresent(renderer);
}

void Sdl2Graphic::windowClear() {
    SDL_RenderClear(renderer);
}

void Sdl2Graphic::windowClose() {
    for (const auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}


size_t Sdl2Graphic::createText(std::string text, std::string fontPath, int size, RColor color) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
    SDL_Surface* surface;
    SDL_Texture* texture;

    if (!font) {
        handleError("Failed to load font");
        return 0;
    }

    surface = TTF_RenderText_Solid(font, text.c_str(), { color.r, color.g, color.b });
    if (!surface) {
        TTF_CloseFont(font);
        handleError("Failed to create surface from text");
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        TTF_CloseFont(font);
        handleError("Failed to create texture from surface");
        return 0;
    }
    textures[nextId] = texture;
    fonts[nextId] = font;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    sprites[nextId] = rect;
    return nextId++;
}

void Sdl2Graphic::setTextPosition(float x, float y, size_t id) {

    sprites[id].x = static_cast<int>(x);
    sprites[id].y = static_cast<int>(y);
}

void Sdl2Graphic::updateText(size_t id, std::string text, int size, RColor color) {
    SDL_Texture* texture;
    TTF_Font* font;
    SDL_Surface* surface;


    if (fonts.find(id) == fonts.end()) {
        handleError("Invalid text ID");
        return;
    }
    SDL_DestroyTexture(textures[id]);
    font = fonts[id];
    surface = TTF_RenderText_Solid(font, text.c_str(), { color.r, color.g, color.b});
    if (!surface) {
        handleError("Failed to create surface from text");
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        handleError("Failed to create texture from surface");
        return;
    }
    textures[id] = texture;
    SDL_Rect& rect = sprites[id];
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
}

void Sdl2Graphic::handleError(const std::string& msg) {
    std::cerr << msg << ": " << SDL_GetError() << std::endl;
}
