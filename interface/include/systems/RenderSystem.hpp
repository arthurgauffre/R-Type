/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#pragma once

#include <components/HitBoxComponent.hpp>
#include <components/SizeComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>

#include <r-type/ASystem.hpp>
#include <r-type/IGraphic.hpp>
#include <r-type/AGraphic.hpp>

namespace ECS_system {
class RenderSystem : virtual public ASystem {
public:
  /**
   * @brief Construct a new RenderSystem object.
   *
   * @param componentManager Reference to the ComponentManager that manages the components.
   * @param graphic Reference to the IGraphic interface for rendering.
   */
  RenderSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager,
               IGraphic &graphic);

  /**
   * @brief Updates the render system by drawing all entities with the appropriate components.
   */
  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities,
              std::vector<std::pair<std::string, size_t>> &msgToSend,
              std::vector<std::pair<std::string, size_t>> &msgReceived) override;
  void initialize() override {}
  void handleComponents() override {}

private:
};
} // namespace ECS_system
