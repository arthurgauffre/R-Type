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

class SfmlGraphic : public AGraphic {
private:
    sf::RenderWindow window;
    std::map<uint32_t, sf::Texture> sfTextures;
    std::map<uint32_t, sf::Sprite> sfSprites;
    std::map<uint32_t, sf::SoundBuffer> sfSoundBuffers;
    std::map<uint32_t, sf::Sound> sfSounds;
    bool gamePaused;

public:
    
    SfmlGraphic()
        : window(sf::VideoMode(800, 600), "R-Type"), gamePaused(false) {}

    virtual ~SfmlGraphic() {}

    void clear();
    void drawSprite(uint32_t SpriteId);
    void setRotation(uint32_t SpriteId, float rotation);
    void setScale(uint32_t SpriteId, float s1, float s2);
    void display();
    void pollEvent();
    void getEventType();
    void closeWindow();
    
    bool loadTexture(uint32_t textureId, const std::string& path) {
        if (sfTextures.find(textureId) != sfTextures.end()) {
            if (!sfTextures[textureId].loadFromFile(path)) {
                std::cerr << "Erreur : Impossible de charger la texture." << std::endl;
                return false;
            }
            return true;
        }
        std::cerr << "Erreur : Texture ID invalide." << std::endl;
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
        } else {
            std::cerr << "Erreur : Sprite ou Texture ID invalide." << std::endl;
        }
    }

    
    void setPosition(uint32_t spriteId, float x, float y) override {
        if (sfSprites.find(spriteId) != sfSprites.end()) {
            sfSprites[spriteId].setPosition(x, y);
        } else {
            std::cerr << "Erreur : Sprite ID invalide." << std::endl;
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
            // Exemple simple : faire descendre tous les sprites à chaque mise à jour
            sf::Vector2f position = sprite.getPosition();
            position.y += 100.0f * deltaTime; // Déplacer de 100 pixels par seconde vers le bas
            sprite.setPosition(position);

            // Ici, vous pourriez aussi ajouter de la logique spécifique à chaque sprite
        }
    }

    void handleEvents() override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    togglePause();
                }
            }
        }
    }

    
    bool isWindowOpen() const override {
        return window.isOpen();
    }

    
    void togglePause() override {
        gamePaused = !gamePaused;
    }

    
    bool isGamePaused() const override {
        return gamePaused;
    }

    
    int setSprite() override {
        uint32_t spriteId = createSprite();
        if (sfSprites.find(spriteId) != sfSprites.end()) {
            sfSprites[spriteId].setPosition(100.0f, 100.0f);
            return 1; // Indique le succès
        }
        return 0; // Indique une erreur
    }
};


