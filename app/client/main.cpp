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

    coreModule.get()->init();

    coreModule.get()->run();
    return 0;
}
