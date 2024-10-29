/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include "include/Game.hpp"
#include <iostream>
#include <r-type/IGraphic.hpp>
#include <SfmlGraphic.hpp>

int main(void)
{
  std::shared_ptr<rtype::CoreModule> coreModule =
      std::make_shared<rtype::CoreModule>();
  SfmlGraphic graphic;

  Game game(coreModule, graphic);
  game.init();
  game.run();
  return 0;
}
