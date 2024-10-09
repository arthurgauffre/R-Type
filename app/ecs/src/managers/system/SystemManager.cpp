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
    // dlopen the render system lib .so
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        renderSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_render_system.so");
    std::shared_ptr<ECS_system::ISystem> renderSystem =
        renderSystemLoader->getInstance("createRenderSystem", componentManager);
    // add the render system to the system manager
    _systems.push_back(renderSystem);
  } else if (systemName == "AudioSystem") {
    // dlopen the audio system lib .so
    std::shared_ptr<
        rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
        audioSystemLoader = std::make_shared<
            rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
            "lib/client_systems/r-type_audio_system.so");
    // get the instance of the audio system
    std::shared_ptr<ECS_system::ISystem> audioSystem =
        audioSystemLoader->getInstance("createAudioSystem", componentManager);
    // add the audio system to the system manager
    _systems.push_back(audioSystem);
  }
}

extern "C" std::shared_ptr<ECS_system::SystemManager> createSystemManager() {
  return std::make_shared<ECS_system::SystemManager>();
}