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

class SfmlGraphic : public AGraphic {
private:
    sf::RenderWindow window;
    std::map<uint32_t, sf::Texture> sfTextures;
    std::map<uint32_t, sf::Sprite> sfSprites;
    std::map<uint32_t, sf::SoundBuffer> sfSoundBuffers;
    std::map<uint32_t, sf::Sound> sfSounds;
    sf::Event event;
    

public:
    
    SfmlGraphic()
        : window(sf::VideoMode(800, 600), "R-Type") {}

    virtual ~SfmlGraphic() {}

    void clear() {
        window.clear();
    }

    void drawSprite(uint32_t SpriteId) {
        if (sfSprites.find(SpriteId) != sfSprites.end()) {
            window.draw(sfSprites[SpriteId]); 
        }
    }

    void setRotation(uint32_t SpriteId, float rotation)
    {
        if (sfSprites.find(SpriteId) != sfSprites.end()) {
            sfSprites[SpriteId].setRotation(rotation);
        }
    }
    void setScale(uint32_t SpriteId, float s1, float s2){
        if (sfSprites.find(SpriteId) != sfSprites.end()) {
            sfSprites[SpriteId].setScale(s1, s2);
        }
    }
    void display(){
        window.display();
    }

 /*   sf::Event::EventType getEventType()
    {
        return event.type;
    }*/
    
    bool loadTexture(uint32_t textureId, const std::string& path) {
        if (sfTextures.find(textureId) != sfTextures.end()) {
            if (!sfTextures[textureId].loadFromFile(path)) {
                return false;
            }
            return true;
        }
        return false;
    }

    
    uint32_t createTexture() override {
        uint32_t textureId = AGraphic::createTexture();
        sfTextures[textureId] = sf::Texture();
        return textureId;
    }

    
    uint32_t createSprite() override {
        uint32_t spriteId = AGraphic::createSprite();
        sfSprites[spriteId] = sf::Sprite();
        return spriteId;
    }

    
    void setTexture(uint32_t spriteId, uint32_t textureId) override {
        if (sfSprites.find(spriteId) != sfSprites.end() && sfTextures.find(textureId) != sfTextures.end()) {
            sfSprites[spriteId].setTexture(sfTextures[textureId]);
    }

    void setPosition(uint32_t spriteId, float x, float y) override {
        if (sfSprites.find(spriteId) != sfSprites.end()) {
            sfSprites[spriteId].setPosition(x, y);
        }
    }

    void render() override {
        window.clear();
        for (auto& spritePair : sfSprites) {
            window.draw(spritePair.second);
        }
        window.display();
    }

    
    void update(float deltaTime) override {
        for (auto& [spriteId, sprite] : sfSprites) {
            sf::Vector2f position = sprite.getPosition();
            position.y += 100.0f * deltaTime; 
            sprite.setPosition(position);

            
        }
    }

    void handleEvents() override {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    
    bool isWindowOpen() const override {
        return window.isOpen();
    }

    int setSprite() override {
        uint32_t spriteId = createSprite();
        if (sfSprites.find(spriteId) != sfSprites.end()) {
            sfSprites[spriteId].setPosition(100.0f, 100.0f);
            return 1;
        }
        return 0; 
    }
    std::pair<int, int> SfmlGraphic::getTextureSize(uint32_t textureId) const {
    auto it = sfTextures.find(textureId);
    if (it != sfTextures.end()) {
        const sf::Texture &texture = it->second;
        return {texture.getSize().x, texture.getSize().y};
    } else 
        return {0, 0};
    }
}

};
