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

  
  virtual void setSpriteAnimation(uint32_t spriteId, uint32_t frameCount,
                                  float animationSpeed) = 0;
  virtual void updateSpriteAnimation(uint32_t spriteId, float deltaTime) = 0;

  
  virtual void render() = 0;

  
  virtual uint32_t createText(const std::string &text,
                              const std::string &fontFile, int fontSize) = 0;
  virtual void setTextPosition(uint32_t textId, float x, float y) = 0;
  virtual void setTextContent(uint32_t textId, const std::string &newText) = 0;
  virtual void renderText(uint32_t textId) = 0;

  
  virtual void getSpriteBoundingBox(uint32_t spriteId, float &x, float &y,
                                    float &width, float &height) = 0;

  
  virtual void handleEvents() = 0;

  
  virtual void togglePause() = 0;
  virtual bool isGamePaused() const = 0;

  
  virtual uint32_t createSound(const std::string &filepath) = 0;
  virtual void playSound(uint32_t soundId) = 0;
  virtual void playMusic(const std::string &filepath) = 0;
  virtual void stopSound(uint32_t soundId) = 0;
  virtual void setSoundVolume(uint32_t soundId, float volume) = 0;
  virtual void stopMusic() = 0;
  virtual void setMusicVolume(float volume) = 0;

  
  virtual void update(float deltaTime) = 0;

  
  virtual void applyShader(uint32_t shaderId) = 0;
  virtual void createShader(const std::string &vertexShaderFile,
                            const std::string &fragmentShaderFile) = 0;
  virtual void applyTransitionEffect(float duration,
                                     const std::string &effectType) = 0;


  virtual void setView(float centerX, float centerY, float width,
                       float height) = 0;
  virtual void resetView() = 0;


  virtual bool isWindowOpen() const = 0;
};

#endif // IGRAPHIC_HPP
