/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AudioSystem
*/

#include <systems/AudioSystem.hpp>

/**
 * @brief Updates the audio system by processing sound and music components of
 * entities.
 *
 * This function iterates through a list of entities and checks for the presence
 * of SoundComponent and MusicComponent in each entity. If a SoundComponent or
 * MusicComponent is found and is marked as playing, the respective play
 * function is called.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be processed.
 */
void ECS_system::AudioSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) {
  for (auto &entity : entities) {
    if (entity->getSceneStatus() != *sceneStatus && entity->getSceneStatus() != Scene::ALL)
      continue;
    component::SoundComponent *soundComponent =
        _componentManager.getComponent<component::SoundComponent>(
            entity->getID());
    component::MusicComponent *musicComponent =
        _componentManager.getComponent<component::MusicComponent>(
            entity->getID());

    if (soundComponent) {
      if (soundComponent->getShouldPlay()) {
        soundComponent->play();
        soundComponent->setShouldPlay(false);
      }
    }
    if (musicComponent) {
      if (!musicComponent->isPlaying())
        musicComponent->play();
    }
  }
}

/**
 * @brief Factory function to create an AudioSystem instance.
 *
 * This function creates and returns a new instance of the AudioSystem class.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 * @param graphic Shared pointer to an IGraphic instance.
 * @param stringCom StringCom instance for communication.
 * @return Pointer to the newly created AudioSystem instance.
 */
EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom) {
  return new ECS_system::AudioSystem(componentManager, entityManager, graphic, stringCom);
}