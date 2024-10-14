/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <Server.hpp>
#include <iostream>
#include <server/Server.hpp>

int main(void) {
  rtype::network::Server server(60000);
  server.Start();

  while (1) {
    server.Update(-1, true);
  }

  return 0;
}
