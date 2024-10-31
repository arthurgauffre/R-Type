/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <RtypeEngine.hpp>
#include <memory>

int main(void) {

    std::shared_ptr<rtype::RtypeEngine> engine = std::make_shared<rtype::RtypeEngine>("sfml");

    // load all systems
    component::ComponentManager &componentManager = *engine->getComponentManager();
    entity::EntityManager &entityManager = *engine->getEntityManager();

    engine->getSystemManager()->addSystem(componentManager, entityManager, "render", engine->_graphic);
    engine->getSystemManager()->addSystem(componentManager, entityManager, "movement", engine->_graphic);
    engine->getSystemManager()->addSystem(componentManager, entityManager, "button", engine->_graphic);
    engine->getSystemManager()->addSystem(componentManager, entityManager, "input", engine->_graphic);
    engine->getSystemManager()->addSystem(componentManager, entityManager, "client", engine->_graphic);

    engine->run();
  return 0;
}
