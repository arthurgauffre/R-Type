/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include <SFML/Graphics.hpp>
#include <components/MusicComponent.hpp>
#include <components/PositionComponent.hpp>
#include <components/SoundComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <limits.h>
#include <r-type/ISystem.hpp>
#include <systems/AudioSystem.hpp>
#include <systems/RenderSystem.hpp>
#include <unistd.h>

int main(void) {
  // unique  ptr to CoreModule
  std::unique_ptr<rtype::CoreModule> coreModule =
      std::make_unique<rtype::CoreModule>();

  coreModule->getEntityManager()->createEntity(0);
  coreModule->getEntityManager()->createEntity(1);

  coreModule->getComponentManager()->addComponent<component::PositionComponent>(
      0, 100.0f, 100.0f);

  coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
      0, 100.0f, 100.0f);

  coreModule->getComponentManager()->addComponent<component::TextureComponent>(
      0, "app/assets/sprites/r-typesheet1.gif");

  coreModule->getComponentManager()->addComponent<component::MusicComponent>(
      0, "app/assets/musics/testSong.wav");

  coreModule->getComponentManager()->addComponent<component::PositionComponent>(
      1, 100.0f, 100.0f);

  coreModule->getComponentManager()->addComponent<component::SpriteComponent>(
      1, 100.0f, 100.0f);

  coreModule->getComponentManager()->addComponent<component::TextureComponent>(
      1, "app/assets/sprites/r-typesheet1.gif");

//   coreModule->getComponentManager()->addComponent<component::SoundComponent>(
//       1, "app/assets/sounds/testSound.wav");

  // load audioSystem .so
  std::shared_ptr<
      rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
      audioSystemLoader = std::make_shared<
          rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
          "lib/client_systems/r-type_audio_system.so");

  // load renderSystem .so
  std::shared_ptr<
      rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
      renderSystemLoader = std::make_shared<
          rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
          "lib/client_systems/r-type_render_system.so");

  component::ComponentManager &componentManager =
      *coreModule->getComponentManager(); // Reference to ComponentManager

  // // Assuming getInstance returns a shared pointer to a concrete type
  coreModule->getSystemManager()->addSystem(componentManager,
  "AudioSystem");

  coreModule->getSystemManager()->addSystem(componentManager, "RenderSystem");

  std::cout << "SystemManager size: "
            << coreModule->getSystemManager()->getSystems().size() << std::endl;
  // main loop

  while (1) {
    coreModule->getSystemManager()->update(
        0.0f, coreModule->getEntityManager()->getEntities());
  }
  return 0;
}
