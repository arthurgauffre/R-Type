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
  rtype::network::Server server(60000);

  server.Start();

  server.run();
  return 0;
}
