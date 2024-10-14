/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include "clientEx.cpp"
#include <memory>

int main(void) {
  // unique  ptr to CoreModule
  std::unique_ptr<rtype::CoreModule> coreModule =
      std::make_unique<rtype::CoreModule>();

  coreModule.get()->init();

  simpleClient();
  coreModule.get()->run();

  return 0;
}

