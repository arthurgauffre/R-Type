/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include <memory>

int main(void) {

    std::shared_ptr<rtype::CoreModule> core = std::make_shared<rtype::CoreModule>();

    // load all systems
    component::ComponentManager &componentManager = *core->getComponentManager();
    entity::EntityManager &entityManager = *core->getEntityManager();

    core->getSystemManager()->addSystem(componentManager, entityManager, "render");
    core->getSystemManager()->addSystem(componentManager, entityManager, "input");
    core->getSystemManager()->addSystem(componentManager, entityManager, "client");

    core->run();
  return 0;
}
