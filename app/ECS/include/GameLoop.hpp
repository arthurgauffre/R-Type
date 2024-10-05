/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameLoop
*/

#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include <SFML/Graphics.hpp>

namespace game
{
  class GameLoop
  {
  public:
    GameLoop(int width, int height, const std::string &title)
        : _width(width), _height(height), _title(title)
    {
      _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _title);
    }
    ~GameLoop() = default;

    void run();

    void update();
    void close();
    void processEvents();

    entity::EntityManager &getEntityManager() { return _entityManager; }
    component::ComponentManager &getComponentManager()
    {
      return _componentManager;
    }
    ECS_system::SystemManager &getSystemManager() { return _systemManager; }

    sf::RenderWindow *getWindow() { return _window; }

  private:
    sf::RenderWindow *_window;
    int _width;
    int _height;
    std::string _title;
    float _deltaTime;

    entity::EntityManager _entityManager;
    component::ComponentManager _componentManager;
    ECS_system::SystemManager _systemManager;
  };
} // namespace game