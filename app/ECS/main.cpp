/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameLoop.hpp"

#include "RenderSystem.hpp"
#include "AudioSystem.hpp"

#include "MusicComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextureComponent.hpp"

int main()
{
    game::GameLoop game(1920, 1080, "R-Type");

    game.getEntityManager().createEntity(0);

    game.getComponentManager().addComponent<component::PositionComponent>(0, 100, 100);
    game.getComponentManager().addComponent<component::SpriteComponent>(0, 100, 100);
    game.getComponentManager().addComponent<component::TextureComponent>(0, "../assets/sprites/r-typesheet1.gif");
    game.getComponentManager().addComponent<component::MusicComponent>(0, "../assets/musics/testSong.wav");
    game.getComponentManager().getComponent<component::MusicComponent>(0)->setLoop(true);

    game.getSystemManager().addSystem<ECS_system::RenderSystem>(game.getComponentManager(), *game.getWindow());
    game.getSystemManager().addSystem<ECS_system::AudioSystem>(game.getComponentManager());

    game.run();

    return 0;
}