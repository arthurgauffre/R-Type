/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputComponent
*/

#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

namespace component {
class InputComponent : public AComponent {
public:
  /**
   * @brief Constructs an InputComponent object.
   *
   * @param entityID The unique identifier of the entity associated with this
   * component.
   */
  InputComponent(uint32_t entityID) : AComponent(entityID) {}

  /**
   * @brief Destroy the InputComponent object.
   */
  ~InputComponent() = default;

  /**
   * @brief Associates an action with a specific key.
   *
   * @param action A string representing the action (e.g., "MoveLeft").
   * @param key The key from the keyboard to bind to this action.
   */
  void bindAction(const std::string &action, sf::Keyboard::Key key) {
    _keyBindings[action] = key;
  }

  sf::Keyboard::Key getBoundKey(const std::string &action) const;

  bool isActionActive(const std::string &action) const;

  /**
   * @brief Updates the input component (empty implementation for now).
   *
   * @param deltaTime The time elapsed since the last update.
   */
  void update(float deltaTime) override {}

private:
  /**
   * @brief Stores key bindings for various actions.
   *
   * The key is a string representing the action (e.g., "MoveLeft"), and the
   * value is the key from the keyboard associated with that action.
   */
  std::unordered_map<std::string, sf::Keyboard::Key> _keyBindings;
};
} // namespace component