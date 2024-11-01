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
KeyBoard
component::InputComponent::getBoundKey(Action action) const {
  auto it = _keyBindings.find(action);
  if (it != _keyBindings.end()) {
    return it->second;
  }
  return KeyBoard::Unknown;
}

/**
 * @brief Checks if a specific action is currently active (key is pressed).
 *
 * @param action The action to check.
 * @return true if the action is active (key is pressed), false otherwise.
 */
bool component::InputComponent::isActionActive(Action action, std::shared_ptr<IGraphic> graphic) const {
  KeyBoard key = getBoundKey(action);

  if (key != KeyBoard::Unknown)
    return graphic->isKeyPressed(key);
  return false;
}

/**
 * @brief Retrieves the key bindings for all actions.
 *
 * @return A map of all key bindings, where the key is the action and the value
 * is the key bound to that action.
 */
std::unordered_map<Action, KeyBoard> component::InputComponent::getKeyBindings() const {
  return _keyBindings;
}

