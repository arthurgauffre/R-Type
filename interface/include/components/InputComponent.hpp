/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>
#include <string>
#include <iostream>
#include <unordered_map>

namespace component {
class InputComponent : public AComponent {
public:
  InputComponent(uint32_t entityID, int numClient) : AComponent(entityID), _numClient(numClient) {};

  /**
   * @brief Destroy the InputComponent object.
   */
  ~InputComponent() = default;

  void update(std::string action, sf::Keyboard::Key key) {
    bindAction(action, key);
  }

  /**
   * @brief Associates an action with a specific key.
   *
   * @param action A string representing the action (e.g., "MoveLeft").
   * @param key The key from the keyboard to bind to this action.
   */
  void bindAction(const std::string &action, sf::Keyboard::Key key) {
    std::cout << "Binding action " << action << " to key " << key << std::endl;
    _keyBindings[action] = key;
  }

  sf::Keyboard::Key getBoundKey(const std::string &action) const;

  bool isActionActive(const std::string &action) const;

  std::unordered_map<std::string, sf::Keyboard::Key> getKeyBindings() const;

  int getNumClient() const { return _numClient; }

private:
  /**
   * @brief Stores key bindings for various actions.
   *
   * The key is a string representing the action (e.g., "MoveLeft"), and the
   * value is the key from the keyboard associated with that action.
   */
  std::unordered_map<std::string, sf::Keyboard::Key> _keyBindings;

  int _numClient = 0;
};
} // namespace component
