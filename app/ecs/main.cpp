/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include <r-type/AEntity.hpp>
#include "EntityManager.hpp"

#include <r-type/AComponent.hpp>
#include "ComponentManager.hpp"
#include <r-type/HitBoxComponent.hpp>
#include <r-type/MusicComponent.hpp>
#include <r-type/PositionComponent.hpp>
#include <r-type/SoundComponent.hpp>
#include <r-type/SpriteComponent.hpp>
#include <r-type/TextureComponent.hpp>

#include <r-type/ASystem.hpp>
#include "AudioSystem.hpp"
#include "CollisionSystem.hpp"
#include "RenderSystem.hpp"
#include "SystemManager.hpp"

int main() {
  entity::EntityManager entityManager;
  component::ComponentManager componentManager;
  ECS_system::SystemManager systemManager;

  entity::IEntity *entity = entityManager.createEntity(0);
  entity::IEntity *entity2 = entityManager.createEntity(1);

  component::PositionComponent *component =
      componentManager.addComponent<component::PositionComponent>(0, 100.0f,
                                                                  100.0f);
  component::SpriteComponent *spriteComponent =
      componentManager.addComponent<component::SpriteComponent>(0, 100.0f,
                                                                100.0f);
  component::TextureComponent *textureComponent =
      componentManager.addComponent<component::TextureComponent>(
          0, "../assets/sprites/r-typesheet1.gif");
  component::HitBoxComponent *hitboxComponent =
      componentManager.addComponent<component::HitBoxComponent>(0, 50.0f,
                                                                50.0f);
  component::MusicComponent *musicComponent =
      componentManager.addComponent<component::MusicComponent>(
          0, "../assets/musics/testSong.wav");

  component::PositionComponent *component2 =
      componentManager.addComponent<component::PositionComponent>(1, 100.0f,
                                                                  100.0f);
  component::SpriteComponent *spriteComponent2 =
      componentManager.addComponent<component::SpriteComponent>(1, 100.0f,
                                                                100.0f);
  component::TextureComponent *textureComponent2 =
      componentManager.addComponent<component::TextureComponent>(
          1, "../assets/sprites/r-typesheet1.gif");
  component::HitBoxComponent *hitboxComponent2 =
      componentManager.addComponent<component::HitBoxComponent>(1, 50.0f,
                                                                50.0f);
  component::SoundComponent *soundComponent =
      componentManager.addComponent<component::SoundComponent>(
          1, "../assets/musics/testSong.wav");

  // create window
  sf::RenderWindow window(sf::VideoMode(800, 600), "ECS");
  systemManager.addSystem<ECS_system::RenderSystem>(componentManager, window);
  systemManager.addSystem<ECS_system::CollisionSystem>(componentManager);
  systemManager.addSystem<ECS_system::AudioSystem>(componentManager);

  // Main loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Update systems
    systemManager.update(0.0f, entityManager.getEntities());
  }

  return 0;
}