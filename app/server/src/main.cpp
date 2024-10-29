/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include "include/Game.hpp"
#include <iostream>

int main(void)
{
  std::shared_ptr<rtype::CoreModule> coreModule =
      std::make_shared<rtype::CoreModule>();
  
  Game game(coreModule);
  game.init();
  game.run();
  return 0;
}
