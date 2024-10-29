/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP
#define IGRAPHIC_HPP

#include <cstdint>
#include <string>

class IGraphic {
public:
  virtual ~IGraphic() = default;
  virtual uint32_t createTexture() = 0;
  virtual uint32_t createSprite() = 0;
  virtual bool loadTexture(uint32_t textureId, const std::string& path) = 0;
  virtual void setTexture(uint32_t spriteId, uint32_t textureId) = 0;
  virtual void setPosition(uint32_t spriteId, float x, float y) = 0;
  virtual int setSprite() = 0;
  virtual std::pair<float, float> getTextureSize(uint32_t textureId) const = 0;

  //virtual void render() = 0;
  virtual void drawSprite(uint32_t SpriteId) = 0;
  virtual void setRotation(uint32_t SpriteId, float rotation) = 0;
  virtual void setScale(uint32_t SpriteId, float s1, float s2) = 0;  
  virtual void handleEvents() = 0;
  //virtual void update(float deltaTime) = 0;
  virtual bool isWindowOpen() const = 0;
  virtual void clear () = 0 ;
  virtual void display() = 0;
  virtual void closeWindow() = 0;
  virtual void updateTexture(uint32_t textureId, const std::string& path) = 0;
  virtual void updateSprite(uint32_t spriteId, float x, float y) = 0;

};

#endif // IGRAPHIC_HPP
