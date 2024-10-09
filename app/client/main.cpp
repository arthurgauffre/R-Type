/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <CoreModule.hpp>
#include <r-type/IEntity.hpp>
#include <components/PositionComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/MusicComponent.hpp>
#include <components/SoundComponent.hpp>
#include <systems/RenderSystem.hpp>
#include <systems/AudioSystem.hpp>

int main(void) {
  // unique  ptr to CoreModule
  std::unique_ptr<rtype::CoreModule> coreModule =
      std::make_unique<rtype::CoreModule>();

//   std::shared_ptr<entity::IEntity> entity1 =
//       coreModule->entityConstructor->getInstance("createEntity", 1);
//   std::shared_ptr<entity::IEntity> entity2 =
//       coreModule->entityConstructor->getInstance("createEntity", 2);
  
//   component::PositionComponent *component =
//       coreModule->getComponentManager()->addComponent<component::PositionComponent>(
//           0, 100.0f, 100.0f);

//   component::SpriteComponent *spriteComponent =
//       coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
//           0, 100.0f, 100.0f);

//   component::TextureComponent *textureComponent =
//       coreModule->getComponentManager()->addComponent<component::TextureComponent>(
//           0, "../assets/sprites/r-typesheet1.gif");
    
//   component::MusicComponent *musicComponent = 
//       coreModule->getComponentManager()->addComponent<component::MusicComponent>(
//           0, "../assets/musics/testSong.wav");
  
//   component::PositionComponent *component2 =
//       coreModule->getComponentManager()->addComponent<component::PositionComponent>(
//           1, 100.0f, 100.0f);

//   component::SpriteComponent *spriteComponent2 =
//       coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
//           1, 100.0f, 100.0f);
  
//   component::TextureComponent *textureComponent2 =
//       coreModule->getComponentManager()->addComponent<component::TextureComponent>(
//           1, "../assets/sprites/r-typesheet1.gif");

//   component::SoundComponent *soundComponent = 
//       coreModule->getComponentManager()->addComponent<component::SoundComponent>(
//           1, "../assets/sounds/testSound.wav");

//   // create window
//   sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");
//   coreModule->getSystemManager()->addSystem<ECS_system::RenderSystem>(
//       *coreModule->getComponentManager(), window);
//   coreModule->getSystemManager()->addSystem<ECS_system::AudioSystem>(
//       *coreModule->getComponentManager(), window);

//   // main loop
//   while (window.isOpen()) {
//     sf::Event event;
//     while (window.pollEvent(event)) {
//       if (event.type == sf::Event::Closed)
//         window.close();
//     }
//     coreModule->getSystemManager()->update(0.0f, coreModule->getEntityManager()->getEntities());
//   }
  return 0;
}
