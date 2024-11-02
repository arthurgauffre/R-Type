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
#include <components/SizeComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/RectangleShapeComponent.hpp>
#include <components/TextComponent.hpp>

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
               entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom);

  /**
   * @brief Destroy the RenderSystem object.
   */
  ~RenderSystem() = default;

  /**
   * @brief Updates the render system.
   *
   * This function updates the render system based on the elapsed time, the list of entities,
   * messages to send, messages received, and the current scene status.
   *
   * @param deltaTime The time elapsed since the last update.
   * @param entities A vector of shared pointers to entities that need to be updated.
   * @param msgToSend A reference to a vector of pairs containing actions and their corresponding entity IDs to be sent.
   * @param msgReceived A reference to a vector of pairs containing messages and their corresponding entity IDs received.
   * @param entityMutex A reference to a mutex for synchronizing access to entities.
   * @param sceneStatus A shared pointer to the current scene status.
   */
  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

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

};
} // namespace ECS_system