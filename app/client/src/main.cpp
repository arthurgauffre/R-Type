/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <Client.hpp>
#include <CoreModule.hpp>
#include <memory>

int main(void) {
  std::shared_ptr<rtype::CoreModule> coreModule =
      std::make_shared<rtype::CoreModule>();
  rtype::network::Client c(coreModule);
  c.Connect("127.0.0.1", 60000);
  c.init();
  c.run();

  return 0;
}
