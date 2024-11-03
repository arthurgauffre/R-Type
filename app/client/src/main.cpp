/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <RtypeEngine.hpp>
#include <memory>
#include <nlohmann/json.hpp>

int main(void)
{
  ECS_system::StringCom stringCom;
  stringCom.texturePath[TexturePath::Player] = "app/assets/sprites/plane.png";
  stringCom.texturePath[TexturePath::Enemy] = "app/assets/sprites/enemy.png";
  stringCom.texturePath[TexturePath::Background] = "app/assets/images/background.jpg";
  stringCom.texturePath[TexturePath::Bullet] = "app/assets/sprites/projectile.gif";
  stringCom.texturePath[TexturePath::Structure] = "app/assets/sprites/block.png";
  stringCom.textFont[TextFont::Arial] = "app/assets/fonts/arial.ttf";
  stringCom.textString[TextString::Play] = "Play";
  stringCom.textString[TextString::Protanopia] = "Protanopia";
  stringCom.textString[TextString::Deuteranopia] = "Deuteranopia";
  stringCom.textString[TextString::Tritanopia] = "Tritanopia";
  stringCom.textString[TextString::ClearFilter] = "Clear Filter";
  stringCom.textString[TextString::KeyBind] = "Key Bind";
  stringCom.textString[TextString::Menu] = "Menu";
  stringCom.textString[TextString::MoveUp] = "Move Up";
  stringCom.textString[TextString::MoveDown] = "Move Down";
  stringCom.textString[TextString::MoveLeft] = "Move Left";
  stringCom.textString[TextString::MoveRight] = "Move Right";
  stringCom.textString[TextString::Shoot] = "Shoot";
  stringCom.textString[TextString::Z] = "Z";
  stringCom.textString[TextString::S] = "S";
  stringCom.textString[TextString::Q] = "Q";
  stringCom.textString[TextString::D] = "D";
  stringCom.textString[TextString::Space] = "Space";
  stringCom.textString[TextString::PressKey] = "Press a key";
  stringCom.soundPath[SoundPath::Shoot] = "app/assets/musics/blaster.wav";
  stringCom.soundPath[SoundPath::BackgroundMusic] = "app/assets/musics/dancin.ogg";

  std::shared_ptr<rtype::RtypeEngine> engine = std::make_shared<rtype::RtypeEngine>("sfml", "sfml");

  component::ComponentManager &componentManager = *engine->getComponentManager();
  entity::EntityManager &entityManager = *engine->getEntityManager();

  std::ifstream file("configs/config1.json");

  if (!file.is_open())
    throw std::runtime_error("Failed to open file: configs/config1.json");

  nlohmann::json _config;

  file >> _config;

  if (_config.contains("localSystems"))
  {
    if (_config["localSystems"].is_array())
    {
      for (const auto &system : _config["localSystems"])
        engine->getSystemManager()->addSystem(componentManager, entityManager, system, engine->_graphic, engine->_audio, stringCom);
    }
  }

  engine->run();
  return 0;
}
