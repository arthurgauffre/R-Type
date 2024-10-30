/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlGraphic
*/

#ifndef SFMLGRAPHIC_HPP_
#define SFMLGRAPHIC_HPP_

#include <r-type/IGraphic.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class SfmlGraphic : public AGraphic {
    public:
        SfmlGraphic(): window(sf::VideoMode(800, 600), "R-Type") {}  
        ~SfmlGraphic() {}
        void clear() override;
        void drawSprite(uint32_t SpriteId) override;
        void setRotation(uint32_t SpriteId, float rotation) override;
        void setScale(uint32_t SpriteId, float s1, float s2) override;
        void display() override;
        void handleEvents() override;
        bool loadTexture(uint32_t textureId, const std::string& path) override;;
        void updateTexture(uint32_t textureId, const std::string& path) override;
        uint32_t createTexture() override;
        uint32_t createSprite() override;
        void setTexture(uint32_t spriteId, uint32_t textureId) override;
        void setPosition(uint32_t spriteId, float x, float y) override;
        std::pair<float, float> getTextureSize(uint32_t textureId) override;
        bool isWindowOpen() const override;

    private:
        sf::RenderWindow window;
        std::map<uint32_t, sf::Texture> sfTextures;
        std::map<uint32_t, sf::Sprite> sfSprites;
        std::map<uint32_t, sf::SoundBuffer> sfSoundBuffers;
        std::map<uint32_t, sf::Sound> sfSounds;
        sf::Event event;  
};

#endif /* !SFMLGRAPHIC_HPP_ */
