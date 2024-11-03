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
component::InputComponent::getBoundKey(Action action) const
{
  auto it = _keyBindings.find(action);
  if (it != _keyBindings.end())
  {
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
bool component::InputComponent::isActionActive(Action action, std::shared_ptr<IGraphic> graphic) const
{
  KeyBoard key = getBoundKey(action);

  if (key != KeyBoard::Unknown)
    return graphic->isKeyPressed(key);
  return false;
}

/**
 * @brief Checks if the given keyboard key is bound to the specified action.
 *
 * @param action The action to check the key binding for.
 * @param key The keyboard key to check.
 * @return true if the key is bound to the action, false otherwise.
 */
KeyBoard component::InputComponent::checkKeyBindings(Action action, KeyBoard key)
{
  std::ifstream file("configs/keyBind.json");

  if (!file.is_open())
    throw std::runtime_error("Failed to open file: configs/keyBind.json");

  nlohmann::json json;

  file >> json;
  file.close();
  try {
    int actionJson = static_cast<int>(action);
    if (json.contains(std::to_string(actionJson))) {
      int keyBind = json[std::to_string(actionJson)];
      return static_cast<KeyBoard>(keyBind);
    } else 
      return key;
  } catch (std::exception &e) {
    return key;
  }
}

/**
 * @brief Updates the input component by binding an action to a keyboard key.
 *
 * @param action The action to be bound.
 * @param key The keyboard key to bind the action to.
 */
void component::InputComponent::update(Action action, KeyBoard key)
{
  bindAction(action, checkKeyBindings(action, key));
}

/**
 * @brief Retrieves the key bindings for all actions.
 *
 * @return A map of all key bindings, where the key is the action and the value
 * is the key bound to that action.
 */
std::unordered_map<Action, KeyBoard> component::InputComponent::getKeyBindings() const
{
  return _keyBindings;
}
