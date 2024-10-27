/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AGraphic
*/

#include <r-type/IGraphic.hpp>

#ifndef AGRAPHIC_HPP
#define AGRAPHIC_HPP

#include "IGraphic.hpp"
#include <unordered_map>
#include <vector>
#include <map>


class AGraphic : public IGraphic {
protected:
  std::map<uint32_t, std::string> textures;
  std::map<uint32_t, uint32_t> sprites;
  uint32_t textureIdCounter;
  uint32_t spriteIdCounter;

public:
  AGraphic() : textureIdCounter(0), spriteIdCounter(0) {}

  virtual ~AGraphic() {}

  virtual uint32_t createTexture() override {
    uint32_t textureId = ++textureIdCounter;
    textures[textureId] = "";
    return textureId;
  }

  virtual uint32_t createSprite() override {
    uint32_t spriteId = ++spriteIdCounter;
    sprites[spriteId] = 0;
    return spriteId;
  }

  virtual void setTexture(uint32_t spriteId, uint32_t textureId) override {
    if (sprites.find(spriteId) != sprites.end() &&
        textures.find(textureId) != textures.end()) {
      sprites[spriteId] = textureId;
    } else {
      // Error Managment
    }
  }
  
  virtual bool loadTexture(uint32_t textureId, const std::string& path) = 0;
  virtual void render() override = 0;
  virtual void setPosition(uint32_t spriteId, float x, float y) override = 0;
  virtual void update(float deltaTime) override = 0;

  virtual int setSprite() override = 0;

  virtual uint32_t createSound(const std::string &filepath) override = 0;
  virtual void playSound(uint32_t soundId) override = 0;

  virtual void handleEvents() override = 0;
  virtual void togglePause() override = 0;
  virtual bool isGamePaused() const override = 0;

  virtual bool isWindowOpen() const override = 0;
  virtual void clear ()  override = 0 ;
  virtual void display()  override = 0;
  virtual void pollEvent()  override = 0;
  virtual void getEventType()  override = 0;
  virtual void closeWindow()  override = 0;
  virtual void drawSprite(uint32_t SpriteId)  override = 0;
  virtual void setRotation(uint32_t SpriteId, float rotation)  override = 0;
  virtual void setScale(uint32_t SpriteId, float s1, float s2)  override = 0;

};

#endif // AGRAPHIC_HPP
