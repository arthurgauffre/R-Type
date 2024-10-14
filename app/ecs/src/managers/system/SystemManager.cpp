/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#include <CoreModule.hpp>
#include <managers/SystemManager.hpp>

ECS_system::SystemManager::SystemManager() {}

/**
 * @brief Updates all systems managed by the SystemManager.
 *
 * This function iterates through all the systems and calls their update method,
 * passing the delta time to each system. Each system handles its own update
 * logic.
 *
 * @param deltaTime The time elapsed since the last update, used to update the
 * systems.
 */
void ECS_system::SystemManager::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &system : _systems) {
    system->update(deltaTime, entities); // Each system updates itself because
                                         // each system has its own logic
  }
}

/**
 * @brief Adds a new system to the manager.
 *
 * This function creates a new system of type T with the provided arguments,
 * stores it in the manager, and returns a pointer to the created system.
 *
 * @tparam T The type of the system to be added.
 * @tparam Args The types of the arguments to be forwarded to the system's
 * constructor.
 * @param args The arguments to be forwarded to the system's constructor.
 * @return T* A pointer to the newly created system.
 */
void ECS_system::SystemManager::addSystem(
    component::ComponentManager &componentManager, std::string systemName) {
  if (systemName == "RenderSystem") {
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        renderSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_render_system.so");

    // Wrap the returned raw pointer in a shared_ptr
    std::shared_ptr<ECS_system::ISystem> renderSystem =
        std::shared_ptr<ECS_system::ISystem>(renderSystemLoader->getInstance(
            "createRenderSystem", componentManager));

    // Add to the systems manager
    _systems.push_back(renderSystem);
  } else if (systemName == "AudioSystem") {
    // dlopen the audio system lib .so
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        audioSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_audio_system.so");

    // Wrap the returned raw pointer in a shared_ptr
    std::shared_ptr<ECS_system::ISystem> audioSystem =
        std::shared_ptr<ECS_system::ISystem>(audioSystemLoader->getInstance(
            "createAudioSystem", componentManager));

    // Add to the systems manager
    _systems.push_back(audioSystem);
  } else if (systemName == "InputSystem") {
    // dlopen the input system lib .so
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        inputSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_input_system.so");

    // Wrap the returned raw pointer in a shared_ptr
    std::shared_ptr<ECS_system::ISystem> inputSystem =
        std::shared_ptr<ECS_system::ISystem>(inputSystemLoader->getInstance(
            "createInputSystem", componentManager));

    // Add to the systems manager
    _systems.push_back(inputSystem);
  } else if (systemName == "MovementSystem") {
    // dlopen the movement system lib .so
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        movementSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_movement_system.so");

    // Wrap the returned raw pointer in a shared_ptr
    std::shared_ptr<ECS_system::ISystem> movementSystem =
        std::shared_ptr<ECS_system::ISystem>(movementSystemLoader->getInstance(
            "createMovementSystem", componentManager));

    // Add to the systems manager
    _systems.push_back(movementSystem);
  } else if (systemName == "BackgroundSystem") {
    // dlopen the background system lib .so
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        backgroundSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_background_system.so");

    // Wrap the returned raw pointer in a shared_ptr
    std::shared_ptr<ECS_system::ISystem> backgroundSystem =
        std::shared_ptr<ECS_system::ISystem>(
            backgroundSystemLoader->getInstance("createBackgroundSystem",
                                                componentManager));

    // Add to the systems manager
    _systems.push_back(backgroundSystem);
  }
}