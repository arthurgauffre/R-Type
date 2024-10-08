/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameLoop.hpp"

#include "AudioSystem.hpp"
#include "BackgroundSystem.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "RenderSystem.hpp"

int main() {
  game::GameLoop game(1920, 1080, "R-Type");

  game.getEntityManager().createEntity(0);

  game.getEntityManager().createEntity(1);

  game.getComponentManager().addComponent<component::PositionComponent>(0, 100,
                                                                        100);
  game.getComponentManager().addComponent<component::SpriteComponent>(0, 100,
                                                                      100);
  game.getComponentManager().addComponent<component::TextureComponent>(
      0, "../assets/sprites/r-typesheet1.gif");
  game.getComponentManager().addComponent<component::TransformComponent>(
      0, sf::Vector2f(100, 100), sf::Vector2f(1, 1));

  sf::Texture texture;
  if (!texture.loadFromFile("../assets/images/city_background.png")) {
    std::cerr << "Failed to load background texture" << std::endl;
    return 1;
  }

  game.getComponentManager().addComponent<component::ScrollComponent>(
      1, sf::Vector2f(100, 0.0f));
  game.getComponentManager().addComponent<component::BackgroundComponent>(
      1, texture, sf::Vector2f(1920, 1080));
  game.getComponentManager().addComponent<component::PositionComponent>(1, 0,
                                                                        0);

  game.getSystemManager().addSystem<ECS_system::BackgroundSystem>(
      game.getComponentManager());

  game.getSystemManager().addSystem<ECS_system::RenderSystem>(
      game.getComponentManager(), *game.getWindow());

  game.run();

  return 0;
}