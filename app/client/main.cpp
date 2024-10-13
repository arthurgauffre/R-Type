/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include <SFML/Graphics.hpp>
#include <components/BackgroundComponent.hpp>
#include <components/InputComponent.hpp>
#include <components/MusicComponent.hpp>
#include <components/PositionComponent.hpp>
#include <components/ScrollComponent.hpp>
#include <components/SoundComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/VelocityComponent.hpp>
#include <iostream>
#include <limits.h>
#include <r-type/ISystem.hpp>
#include <systems/AudioSystem.hpp>
#include <systems/RenderSystem.hpp>
#include <unistd.h>

int main(void)
{
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

    coreModule->getComponentManager()->addComponent<component::InputComponent>(0);

    coreModule->getComponentManager()->addComponent<component::VelocityComponent>(
        0, sf::Vector2f(10.0f, 0.0f));

    coreModule->getComponentManager()
        ->addComponent<component::TransformComponent>(
            0, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1.0f, 1.0f));

    coreModule->getComponentManager()->addComponent<component::PositionComponent>(
        1, 0.0f, 0.0f);

    coreModule->getComponentManager()->addComponent<component::ScrollComponent>(
        1, sf::Vector2f(100.0f, 0.0f));

    coreModule->getComponentManager()
        ->addComponent<component::BackgroundComponent>(
            1, "app/assets/images/city_background.png", sf::Vector2f(1920.0f, 1080.0f));

    component::ComponentManager &componentManager =
        *coreModule->getComponentManager(); // Reference to ComponentManager

    // // Assuming getInstance returns a shared pointer to a concrete type
    coreModule->getSystemManager()->addSystem(componentManager, "AudioSystem");

    coreModule->getSystemManager()->addSystem(componentManager, "RenderSystem");

    coreModule->getSystemManager()->addSystem(componentManager, "InputSystem");

    coreModule->getSystemManager()->addSystem(componentManager, "MovementSystem");

    coreModule->getSystemManager()->addSystem(componentManager,
                                              "BackgroundSystem");

    coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(0)
        ->bindAction("MoveLeft", sf::Keyboard::A);

    coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(0)
        ->bindAction("MoveRight", sf::Keyboard::D);

    coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(0)
        ->bindAction("MoveUp", sf::Keyboard::W);

    coreModule->getComponentManager()
        ->getComponent<component::InputComponent>(0)
        ->bindAction("MoveDown", sf::Keyboard::S);

    std::cout << "SystemManager size: "
              << coreModule->getSystemManager()->getSystems().size() << std::endl;

    std::cout << "Texture background size :" << coreModule.get()->getComponentManager()->getComponent<component::BackgroundComponent>(1)->getSprite().getTexture()->getSize().x << " " << coreModule.get()->getComponentManager()->getComponent<component::BackgroundComponent>(1)->getSprite().getTexture()->getSize().y << std::endl;

    sf::Clock clock;
    while (1)
    {
        float deltatime = clock.restart().asSeconds();
        coreModule->getSystemManager()->update(
            deltatime, coreModule->getEntityManager()->getEntities());
    }
    return 0;
}
