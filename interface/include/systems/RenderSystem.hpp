/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#pragma once

#include <components/BackgroundComponent.hpp>
#include <components/PositionComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <r-type/ASystem.hpp>

namespace ECS_system {
class RenderSystem : virtual public ASystem {
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
               entity::EntityManager &entityManager);

  /**
   * @brief Destroy the RenderSystem object.
   */
  ~RenderSystem() = default;

  // bool getGameClosed() const { return _gameClosed; }

  std::vector<std::string>
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::string> msgToSend) override;

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
  sf::RenderWindow _window;
  sf::Event _event;
  // bool _gameClosed = false;
};
} // namespace ECS_system