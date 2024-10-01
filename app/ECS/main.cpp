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
#include "InputSystem.hpp"
#include "RenderSystem.hpp"

#include "MusicComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextureComponent.hpp"
#include "InputComponent.hpp"

int main() {
  game::GameLoop game(1920, 1080, "R-Type");

  game.getEntityManager().createEntity(0);

    game.getComponentManager().addComponent<component::PositionComponent>(0, 100, 100);
    game.getComponentManager().addComponent<component::SpriteComponent>(0, 100, 100);
    game.getComponentManager().addComponent<component::TextureComponent>(0, "../assets/sprites/r-typesheet1.gif");
    game.getComponentManager().addComponent<component::MusicComponent>(0, "../assets/musics/testSong.wav");
    game.getComponentManager().addComponent<component::InputComponent>(0);


    game.getSystemManager().addSystem<ECS_system::RenderSystem>(game.getComponentManager(), *game.getWindow());
    game.getSystemManager().addSystem<ECS_system::InputSystem>(game.getComponentManager());

    game.getComponentManager().getComponent<component::InputComponent>(0)->bindAction("MoveLeft", sf::Keyboard::A);
    game.getComponentManager().getComponent<component::InputComponent>(0)->bindAction("MoveRight", sf::Keyboard::D);
    game.getComponentManager().getComponent<component::InputComponent>(0)->bindAction("MoveUp", sf::Keyboard::W);
    game.getComponentManager().getComponent<component::InputComponent>(0)->bindAction("MoveDown", sf::Keyboard::S);

  game.run();

  return 0;
}