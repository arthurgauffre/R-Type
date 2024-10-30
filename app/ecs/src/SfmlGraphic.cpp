/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#include "AGraphic.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <IGraphic.hpp>
#include <AGraphic.hpp>
#include <SfmlGraphic.hpp>


void SfmlGraphic::clear() {
    window.clear();
}

void SfmlGraphic::drawSprite(uint32_t SpriteId) {
    if (sfSprites.find(SpriteId) != sfSprites.end()) {
        window.draw(sfSprites[SpriteId]); 
    }
}

void SfmlGraphic::setRotation(uint32_t SpriteId, float rotation) {
    if (sfSprites.find(SpriteId) != sfSprites.end()) {
        sfSprites[SpriteId].setRotation(rotation);
    }
}

void SfmlGraphic::setScale(uint32_t SpriteId, float s1, float s2) {
    if (sfSprites.find(SpriteId) != sfSprites.end()) {
        sfSprites[SpriteId].setScale(s1, s2);
    }
}

void SfmlGraphic::display() {
    window.display();
}

//sf::Event::EventType getEventType() {
    //return event.type;
//}
    
bool SfmlGraphic::loadTexture(uint32_t textureId, const std::string& path) {
    if (sfTextures.find(textureId) != sfTextures.end()) {
        if (!sfTextures[textureId].loadFromFile(path)) {
            return false;
        }
            return true;
    }
    return false;
}

void SfmlGraphic::updateTexture(uint32_t textureId, const std::string& path)
{
    if (sfTextures.find(textureId) != sfTextures.end()) {
        sfTextures[textureId].loadFromFile(path);
    }
}

uint32_t SfmlGraphic::createTexture()  {
    uint32_t textureId = AGraphic::createTexture();
    sfTextures[textureId] = sf::Texture();
    return textureId;
}

    
uint32_t SfmlGraphic::createSprite()  {
    uint32_t spriteId = AGraphic::createSprite();
    sfSprites[spriteId] = sf::Sprite();
    return spriteId;
}

    
void SfmlGraphic::setTexture(uint32_t spriteId, uint32_t textureId)  {
    if (sfSprites.find(spriteId) != sfSprites.end() && sfTextures.find(textureId) != sfTextures.end()) {
        sfSprites[spriteId].setTexture(sfTextures[textureId]);
    }
}
  
void SfmlGraphic::setPosition(uint32_t spriteId, float x, float y)  {
    if (sfSprites.find(spriteId) != sfSprites.end()) {
        sfSprites[spriteId].setPosition(x, y);
    }
}
    
void SfmlGraphic::handleEvents()  {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
    
bool SfmlGraphic::isWindowOpen() const  {
    return window.isOpen();
}

std::pair<float, float> getTextureSize(uint32_t textureId) {
    const auto& texture = sfTextures.at(textureId);
    auto size = texture.getSize();
    return {static_cast<float>(size.x), static_cast<float>(size.y)};
}
