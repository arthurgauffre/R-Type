/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "Client.cpp"
#include <Client.hpp>
#include <memory>

int main(void) {
  rtype::network::Client c;
  c.Connect("127.0.0.1", 60000);
  c.run();
  return 0;
}
