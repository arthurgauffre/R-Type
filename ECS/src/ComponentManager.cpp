/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

/**
 * @brief Adds a new component of type T to the specified entity.
 *
 * This function creates a new component of type T, initializes it with the provided arguments,
 * and associates it with the given entity ID. The component is stored in a unique pointer and
 * added to the component list of the specified entity.
 *
 * @tparam T The type of the component to be added.
 * @tparam Args The types of the arguments used to initialize the component.
 * @param entityID The ID of the entity to which the component will be added.
 * @param args The arguments used to initialize the component.
 * @return T* A pointer to the newly created component.
 */
template <typename T, typename... Args>
T *component::ComponentManager::AddComponent(uint32_t entityID, Args &&...args)
{
    auto component = std::make_unique<T>(entityID, std::forward<Args>(args)...);
    T *ptr = component.get();
    components[entityID].push_back(std::move(component));
    return ptr;
}

/**
 * @brief Retrieves a component of type T associated with a given entity ID.
 *
 * This function searches through the components associated with the specified
 * entity ID and attempts to dynamically cast each component to the requested type T.
 * If a component of the requested type is found, it is returned. Otherwise, the function
 * returns nullptr.
 *
 * @tparam T The type of the component to retrieve.
 * @param entityID The ID of the entity whose component is to be retrieved.
 * @return T* A pointer to the component of type T if found, otherwise nullptr.
 */
template <typename T>
T *component::ComponentManager::GetComponent(uint32_t entityID)
{
    const auto &entityComponents = components[entityID];

    for (const auto &component : entityComponents)
    {
        if (T *casted = dynamic_cast<T *>(component.get()))
            return casted;
    }

    return nullptr;
}

/**
 * @brief Updates all active components for each entity.
 *
 * This function iterates through all the components of each entity and calls
 * their update method if they are active. The update method is called with
 * the given delta time.
 *
 * @param deltaTime The time elapsed since the last update, used to update the components.
 */
void component::ComponentManager::update(float deltaTime)
{
    for (auto &entityComponents : components)
    {
        for (auto &component : entityComponents.second)
        {
            if (component->getActive())
                component->update(deltaTime);
        }
    }
}