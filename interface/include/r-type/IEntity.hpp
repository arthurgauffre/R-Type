/*
** EPITECH PROJECT, 2024
** *
** File description:
** IEntity
*/

#pragma once
#ifdef _WIN32
#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <cstdint>
#include <r-type/Enum.hpp>

namespace entity {
enum class EntityCommunication {
  NONE,
  CREATE,
  UPDATE,
  DELETE,
};
class IEntity {
public:
  /**
   * @brief Default constructor for the IEntity class.
   */
  IEntity() = default;
  /**
   * @brief Virtual destructor for the IEntity class.
   */
  virtual ~IEntity() = default;

    /**
     * @brief Get the unique identifier of the entity.
     *
     * This function returns the unique ID assigned to the entity.
     *
     * @return uint32_t The unique identifier of the entity.
     */
    virtual uint32_t getID() const = 0;

    /**
     * @brief Sets the active state of the entity.
     *
     * This method is used to enable or disable the entity. When an entity is
     * active, it participates in the game loop and can be updated and rendered.
     * When it is inactive, it is ignored by the game loop.
     *
     * @param active A boolean value indicating whether the entity should be
     * active (true) or inactive (false).
     */
    virtual void setActive(bool active) = 0;

    /**
     * @brief Checks if the entity is active.
     *
     * This pure virtual function must be implemented by derived classes to
     * determine whether the entity is currently active.
     *
     * @return true if the entity is active, false otherwise.
     */
    virtual bool getActive() const = 0;

    /**
     * @brief Retrieves the communication status of the entity.
     *
     * This method is used to determine the current communication status of the
     * entity.
     *
     * @return EntityCommunication The current communication status of the entity.
     */
    virtual EntityCommunication getCommunication() const = 0;

    /**
     * @brief Sets the communication status of the entity.
     *
     * This method is used to set the communication status of the entity to the
     * specified value.
     *
     * @param status The new communication status for the entity.
     */
    virtual void setCommunication(EntityCommunication status) = 0;

    /**
     * @brief Retrieves the scene status of the entity.
     *
     * This method is used to determine the current scene status of the entity.
     *
     * @return Scene The current scene status of the entity.
     */
    virtual Scene getSceneStatus() const = 0;

    /**
     * @brief Sets the scene status of the entity.
     *
     * This method is used to set the scene status of the entity to the specified
     * value.
     *
     * @param status The new scene status for the entity.
     */
    virtual void setSceneStatus(Scene status) = 0;

    /**
     * @brief Retrieves the number of the client associated with the entity.
     *
     * This method is used to determine the number of the client associated with
     * the entity.
     *
     * @return int The number of the client associated with the entity.
     */
    virtual int getNumClient() const = 0;

    /**
     * @brief Sets the number of the client associated with the entity.
     *
     * This method is used to set the number of the client associated with the
     * entity to the specified value.
     *
     * @param numClient The new number of the client associated with the entity.
     */
    virtual void setNumClient(int numClient) = 0;

  protected:
    /**
     * @brief Represents the communication status of an entity.
     *
     * This enum class is used to define the various communication statuses
     * that an entity can have within the system. The possible values include:
     * - CREATE: Indicates that the entity is in the creation state.
     * - UPDATE: Indicates that the entity is in the update state.
     * - DELETE: Indicates that the entity is in the deletion state.
     */
    EntityCommunication communicationStatus{EntityCommunication::CREATE};

    /**
     * @brief Represents the current status of the scene.
     *
     * This variable holds the status of the scene, which is of type Scene.
     * The initial value is set to Scene::GAME.
     */
    Scene sceneStatus{Scene::GAME};
};
} // namespace entity
