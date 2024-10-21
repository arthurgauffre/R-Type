/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include <ServerSystem.hpp>
#include <iostream>

int main(void) {
  std::shared_ptr<rtype::CoreModule> coreModule = std::make_shared<rtype::CoreModule>();

  component::ComponentManager &componentManager = *coreModule->getComponentManager();
  entity::EntityManager &entityManager = *coreModule->getEntityManager();

  coreModule->getSystemManager()->addSystem(componentManager, entityManager, "server");

  // rtype::network::ServerSystem server(componentManager, entityManager);
  coreModule->run();
  return 0;
}
