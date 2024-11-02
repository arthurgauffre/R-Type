/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ServerSystem
*/

#include <systems/ServerSystem.hpp>

namespace rtype::network
{

  /**
   * @brief Creates a new ServerSystem instance.
   *
   * This function creates and returns a new instance of the ServerSystem class
   * with the specified component manager, entity manager, graphic interface,
   * and string communication interface.
   *
   * @param componentManager Reference to the ComponentManager instance.
   * @param entityManager Reference to the EntityManager instance.
   * @param graphic Shared pointer to the IGraphic interface.
   * @param stringCom String communication interface.
   * @return Pointer to the newly created ServerSystem instance.
   */
  EXPORT_API ECS_system::ISystem *
  createSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom)
  {
    return new ServerSystem<NetworkMessages>(componentManager, entityManager, graphic, stringCom);
  }
} // namespace rtype::network