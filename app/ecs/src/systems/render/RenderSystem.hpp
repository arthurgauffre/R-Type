/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#pragma once

#include <r-type/ASystem.hpp>
#include <r-type/PositionComponent.hpp>
#include <SFML/Graphics.hpp>
#include <r-type/SpriteComponent.hpp>
#include <r-type/TextureComponent.hpp>

namespace ECS_system {
class RenderSystem : public ASystem {
public:
  /**
   * @brief Construct a new RenderSystem object.
   *
   * @param componentManager Reference to the ComponentManager that manages the
   * components.
   * @param window Reference to the SFML RenderWindow where the rendering will
   * take place.
   */
  RenderSystem(component::ComponentManager &componentManager,
               sf::RenderWindow &window)
      : ASystem(componentManager), _window(window){};

  /**
   * @brief Destroy the RenderSystem object.
   */
  ~RenderSystem() = default;

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities) override;

  /**
   * @brief Initializes the render system.
   *
   * This method is called to set up any necessary resources or configurations
   * required by the render system before it starts processing.
   */
  void initialize() override{};

  /**
   * @brief Handles the components associated with the RenderSystem.
   *
   * This function is an override of the base class method and is responsible
   * for managing the components that are relevant to the rendering system. The
   * actual implementation details should be provided in the function body.
   */
  void handleComponents() override{};

private:
  /**
   * @brief Reference to the SFML RenderWindow used for rendering.
   *
   * This member variable holds a reference to the SFML RenderWindow object
   * that is used by the RenderSystem to draw and display graphical content.
   * It is expected to be initialized and managed outside of this class.
   */
  sf::RenderWindow &_window;
};
} // namespace ECS_system