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
  /**
   * @brief Constructs a new InputComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param numClient The client number associated with this input component.
   */
  InputComponent(uint32_t entityID, int numClient) : AComponent(entityID), _numClient(numClient) {};

  /**
   * @brief Destroy the InputComponent object.
   */
  ~InputComponent() = default;

  /**
   * @brief Updates the input component by binding an action to a keyboard key.
   *
   * @param action The action to be bound.
   * @param key The keyboard key to bind the action to.
   */
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

  /**
   * @brief Retrieves the keyboard key bound to a specific action.
   *
   * @param action The action for which the bound key is to be retrieved.
   * @return KeyBoard The keyboard key bound to the specified action.
   */
  KeyBoard getBoundKey(Action action) const;

  /**
   * @brief Checks if a specific action is currently active.
   *
   * @param action The action to check.
   * @param graphic A shared pointer to an IGraphic instance.
   * @return true if the action is active, false otherwise.
   */
  bool isActionActive(Action action, std::shared_ptr<IGraphic> graphic) const;

  /**
   * @brief Retrieves the current key bindings for actions.
   *
   * This function returns a map that associates each action with a corresponding keyboard key.
   *
   * @return std::unordered_map<Action, KeyBoard> A map containing the key bindings for actions.
   */
  std::unordered_map<Action, KeyBoard> getKeyBindings() const;

  /**
   * @brief Get the number of clients.
   *
   * @return int The number of clients.
   */
  int getNumClient() const { return _numClient; }

  /**
   * @brief Retrieves the key bindings for actions.
   *
   * This function returns a reference to the unordered map that associates
   * actions with their corresponding keyboard keys.
   *
   * @return std::unordered_map<Action, KeyBoard>& Reference to the key bindings map.
   */
  std::unordered_map<Action, KeyBoard> &getKeyBindings() { return _keyBindings; }

private:
  /**
   * @brief Stores key bindings for various actions.
   *
   * The key is a string representing the action (e.g., "MoveLeft"), and the
   * value is the key from the keyboard associated with that action.
   */
  std::unordered_map<Action, KeyBoard> _keyBindings;

  /**
   * @brief The number of clients.
   *
   * This variable keeps track of the number of clients connected or interacting
   * with the system. It is initialized to 0.
   */
  int _numClient = 0;
};
} // namespace component
