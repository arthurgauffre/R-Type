/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputComponent
*/

#include <components/InputComponent.hpp>

/**
 * @brief Retrieves the key associated with a specific action.
 *
 * @param action The action whose associated key is to be retrieved.
 * @return The key bound to the action, or sf::Keyboard::Unknown if the action
 * is not found.
 */
sf::Keyboard::Key
component::InputComponent::getBoundKey(const std::string &action) const {
  auto it = _keyBindings.find(action);
  if (it != _keyBindings.end()) {
    return it->second;
  }
  return sf::Keyboard::Unknown;
}

/**
 * @brief Checks if a specific action is currently active (key is pressed).
 *
 * @param action The action to check.
 * @return true if the action is active (key is pressed), false otherwise.
 */
bool component::InputComponent::isActionActive(
    const std::string &action) const {
  sf::Keyboard::Key key = getBoundKey(action);

  if (key != sf::Keyboard::Unknown) {
    return sf::Keyboard::isKeyPressed(key);
  }
  return false;
}

/**
 * @brief Retrieves the key bindings for all actions.
 *
 * @return A map of all key bindings, where the key is the action and the value
 * is the key bound to that action.
 */
std::unordered_map<std::string, sf::Keyboard::Key> component::InputComponent::getKeyBindings() const {
  return _keyBindings;
}

