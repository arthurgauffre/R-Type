/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <RtypeEngine.hpp>
#include <memory>

int main(void)
{
  ECS_system::StringCom stringCom;
  stringCom.texturePath[TexturePath::Player] = "app/assets/sprites/plane.png";
  stringCom.texturePath[TexturePath::Enemy] = "app/assets/sprites/enemy.png";
  stringCom.texturePath[TexturePath::Background] = "app/assets/images/city_background.png";
  stringCom.texturePath[TexturePath::Bullet] = "app/assets/sprites/projectile.gif";
  stringCom.texturePath[TexturePath::Structure] = "app/assets/sprites/block.png";
  stringCom.textFont[TextFont::Arial] = "app/assets/fonts/arial.ttf";
  stringCom.textString[TextString::Play] = "Play";
  stringCom.textString[TextString::Protanopia] = "Protanopia";
  stringCom.textString[TextString::Deuteranopia] = "Deuteranopia";
  stringCom.textString[TextString::Tritanopia] = "Tritanopia";
  stringCom.textString[TextString::ClearFilter] = "Clear Filter";

  std::shared_ptr<rtype::RtypeEngine> engine = std::make_shared<rtype::RtypeEngine>("sfml");

  component::ComponentManager &componentManager = *engine->getComponentManager();
  entity::EntityManager &entityManager = *engine->getEntityManager();

  engine->getSystemManager()->addSystem(componentManager, entityManager, "render", engine->_graphic, stringCom);
  engine->getSystemManager()->addSystem(componentManager, entityManager, "movement", engine->_graphic, stringCom);
  engine->getSystemManager()->addSystem(componentManager, entityManager, "button", engine->_graphic, stringCom);
  engine->getSystemManager()->addSystem(componentManager, entityManager, "input", engine->_graphic, stringCom);
  engine->getSystemManager()->addSystem(componentManager, entityManager, "client", engine->_graphic, stringCom);

  engine->run();
  return 0;
}
