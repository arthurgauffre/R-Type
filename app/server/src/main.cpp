/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <RtypeEngine.hpp>
#include "include/Game.hpp"
#include <iostream>

int main(void)
{
  std::shared_ptr<rtype::RtypeEngine> coreModule =
      std::make_shared<rtype::RtypeEngine>();
  Game game(coreModule);
  game.init();
  game.run();
  return 0;
}
