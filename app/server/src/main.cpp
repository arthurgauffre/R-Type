/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include <Server.hpp>
#include <iostream>

int main(void) {
  std::shared_ptr<rtype::CoreModule> coreModule =
      std::make_unique<rtype::CoreModule>();
  rtype::network::Server server(60000, coreModule);

  server.Start();

  server.run();
  return 0;
}
