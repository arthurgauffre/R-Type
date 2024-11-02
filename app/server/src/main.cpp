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
  std::shared_ptr<rtype::RtypeEngine> engine =
      std::make_shared<rtype::RtypeEngine>("sfml", "sfml");
  Game game(engine);
  game.init();
  game.run();
  return 0;
}
