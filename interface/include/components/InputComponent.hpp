/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <r-type/Enum.hpp>
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

  void update(Action action, KeyBoard key) {
    bindAction(action, key);
  }

  /**
   * @brief Associates an action with a specific key.
   *
   * @param action A string representing the action (e.g., "MoveLeft").
   * @param key The key from the keyboard to bind to this action.
   */
  void bindAction(Action action, KeyBoard key) {
    _keyBindings[action] = key;
  }

  KeyBoard getBoundKey(Action action) const;

  bool isActionActive(Action action, std::shared_ptr<IGraphic> graphic) const;

  std::unordered_map<Action, KeyBoard> getKeyBindings() const;

  int getNumClient() const { return _numClient; }

  std::unordered_map<Action, KeyBoard> &getKeyBindings() { return _keyBindings; }

private:
  /**
   * @brief Stores key bindings for various actions.
   *
   * The key is a string representing the action (e.g., "MoveLeft"), and the
   * value is the key from the keyboard associated with that action.
   */
  std::unordered_map<Action, KeyBoard> _keyBindings;

  int _numClient = 0;
};
} // namespace component
