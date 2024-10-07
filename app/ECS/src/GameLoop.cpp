/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

void game::GameLoop::run() {
  while (_window->isOpen()) {
    _deltaTime = _clock.restart().asSeconds();
    processEvents();
    update();
  }
}

void game::GameLoop::update() {
  _systemManager.update(_deltaTime, _entityManager.getEntities());
}

void game::GameLoop::close() { _window->close(); }

void game::GameLoop::processEvents() {
  sf::Event event;
  while (_window->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      close();
  }
}