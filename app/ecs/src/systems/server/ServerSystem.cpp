/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ServerSystem
*/

#include <systems/ServerSystem.hpp>

namespace rtype::network
{

  EXPORT_API ECS_system::ISystem *
  createSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom)
  {
    return new ServerSystem<NetworkMessages>(componentManager, entityManager, graphic, stringCom);
  }
} // namespace rtype::network