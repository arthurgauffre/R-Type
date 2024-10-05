/*
** EPITECH PROJECT, 2024
** *
** File description:
** ComponentManager
*/

#pragma once

#include "IComponent.hpp"
#include "IEntity.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace component
{
  class ComponentManager
  {
  public:
    /**
     * @brief Adds a new component of type T to the specified entity.
     *
     * This function creates a new component of type T, initializes it with the
     * provided arguments, and associates it with the given entity ID. The
     * component is stored in the internal component container and a pointer to
     * the newly created component is returned.
     *
     * @tparam T The type of the component to be added.
     * @tparam Args The types of the arguments to be forwarded to the component's
     * constructor.
     * @param entityID The ID of the entity to which the component will be added.
     * @param args The arguments to be forwarded to the component's constructor.
     * @return T* A pointer to the newly created component.
     */
    template <typename T, typename... Args>
    T *addComponent(uint32_t entityID, Args &&...args)
    {
      auto component = std::make_unique<T>(entityID, std::forward<Args>(args)...);
      T *ptr = component.get();
      _components[entityID].push_back(std::move(component));
      return ptr;
    }

    /**
     * @brief Retrieves a component of type T associated with a given entity ID.
     *
     * This function searches for the specified entity ID in the component map.
     * If found, it iterates through the components associated with the entity
     * and attempts to dynamically cast each component to the specified type T.
     * If a component of type T is found, it is returned. Otherwise, the function
     * returns nullptr.
     *
     * @tparam T The type of the component to retrieve.
     * @param entityID The ID of the entity whose component is to be retrieved.
     * @return T* Pointer to the component of type T if found, otherwise nullptr.
     */
    template <typename T>
    T *getComponent(uint32_t entityID)
    {
      auto it = _components.find(entityID);
      if (it == _components.end())
        return nullptr;

      const auto &entityComponents = it->second;

      for (const auto &component : entityComponents)
      {
        if (T *casted = dynamic_cast<T *>(component.get()))
          return casted;
      }
      return nullptr;
    }

    /**
     * @brief Checks if the specified entity has all the given components.
     *
     * This template function takes a variadic list of component types and checks
     * if the entity has all of these components. It returns true if the entity
     * has all the specified components, otherwise it returns false.
     *
     * @tparam Components The types of the components to check for.
     * @param entity A shared pointer to the entity to check.
     * @return true if the entity has all the specified components, false
     * otherwise.
     */
    template <typename... Components>
    bool hasComponents(std::shared_ptr<entity::IEntity> entity)
    {
      return (... && (getComponent<Components>(entity->getID()) != nullptr));
    }

    /**
     * @brief Retrieves entities that have the specified components.
     *
     * This function filters the provided list of entities and returns a new list
     * containing only those entities that possess all of the specified
     * components.
     *
     * @tparam Components The types of components to check for.
     * @param entities A vector of shared pointers to IEntity objects to be
     * filtered.
     * @return A vector of shared pointers to IEntity objects that have all the
     * specified components.
     */
    template <typename... Components>
    std::vector<std::shared_ptr<entity::IEntity>> getEntitiesWithComponents(
        const std::vector<std::shared_ptr<entity::IEntity>> &entities)
    {
      std::vector<std::shared_ptr<entity::IEntity>> result;

      for (const auto &entity : entities)
      {
        if (entity && hasComponents<Components...>(entity))
          result.push_back(entity);
      }

      return result;
    }

    void update(float deltaTime);

  private:
    /**
     * @brief A map that associates entity IDs with their respective components.
     *
     * This unordered map uses a 32-bit unsigned integer as the key, representing
     * the entity ID. The value is a vector of unique pointers to IComponent,
     * which holds the components associated with the entity.
     */
    std::unordered_map<uint32_t, std::vector<std::unique_ptr<IComponent>>>
        _components;
  };
} // namespace component
