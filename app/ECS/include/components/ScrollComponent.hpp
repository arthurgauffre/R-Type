/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScrollComponent
*/

#pragma once

#include "AComponent.hpp"
#include <SFML/System/Vector2.hpp>

namespace component
{
    class ScrollComponent : public AComponent
    {
    public:
        ScrollComponent(uint32_t entityID, sf::Vector2f speed);
        ~ScrollComponent() = default;

        const sf::Vector2f getScrollSpeed();

        void setScrollSpeed(const sf::Vector2f &speed);

        void update(float deltaTime) override {};

    private:
        sf::Vector2f _scrollSpeed;
    };
}