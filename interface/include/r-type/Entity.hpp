/*
** EPITECH PROJECT, 2024
** *
** File description:
** Entity
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#pragma once

#include <memory>
#include <r-type/IEntity.hpp>

namespace entity {
class DLL_EXPORT  Entity : virtual public IEntity {
public:
  /**
   * @brief Constructs an Entity object with a specified ID and sets it as
   * active.
   *
   * @param id The unique identifier for the entity.
   */
  Entity(uint32_t id, int numClt);

  /**
   * @brief Destroy the Entity object.
   */
  virtual ~Entity();

  /**
   * @brief Retrieves the unique identifier of the entity.
   *
   * @return uint32_t The unique identifier of the entity.
   */
  uint32_t getID() const override;

  /**
   * @brief Sets the active state of the entity.
   *
   * This function overrides the base class implementation to set the active
   * state of the entity. When an entity is active, it is considered in use and
   * will be processed by the system. When inactive, it will be ignored.
   *
   * @param active A boolean value indicating the desired active state.
   *               - true: The entity is active.
   *               - false: The entity is inactive.
   */
  void setActive(bool active) override;

  /**
   * @brief Retrieves the active status of the entity.
   *
   * @return true if the entity is active, false otherwise.
   */
  bool getActive() const override;

  /**
   * @brief Retrieves the communication status of the entity.
   *
   * This method is used to determine the current communication status of the
   * entity.
   *
   * @return EntityCommunication The current communication status of the entity.
   */
  EntityCommunication getCommunication() const override;


  /**
   * @brief Sets the communication object for the entity.
   *
   * This function overrides the base class implementation to set the
   * communication object which is used for inter-entity communication.
   *
   * @param communication The EntityCommunication object to be set.
   */
  void setCommunication(EntityCommunication communication) override;

  /**
   * @brief Retrieves the current status of the scene.
   *
   * This function overrides the base class implementation to provide
   * the current status of the scene associated with the entity.
   *
   * @return Scene The current status of the scene.
   */
  Scene getSceneStatus() const override;

  /**
   * @brief Sets the status of the scene.
   *
   * This function overrides the base class method to set the current status
   * of the scene to the provided status.
   *
   * @param status The new status to set for the scene.
   */
  void setSceneStatus(Scene status) override;

  /**
   * @brief Set the number of clients associated with the entity.
   *
   * This function sets the number of clients associated with the entity.
   *
   * @param numClient The number of clients.
   */
  void setNumClient(int numClient) override;

  /**
   * @brief Get the number of clients.
   *
   * This function returns the number of clients connected or associated with the entity.
   *
   * @return int The number of clients.
   */
  int getNumClient() const override;

protected:
  /**
   * @brief Unique identifier for the entity.
   *
   * This ID is used to distinguish each entity within the ECS (Entity Component
   * System).
   */
  uint32_t id;

  /**
   * @brief Indicates whether the entity is currently active.
   *
   * This boolean flag is used to determine if the entity is active and should
   * be processed in the game loop. If set to true, the entity is active; if
   * false, the entity is inactive.
   */
  bool isActive;

  /**
   * @brief Represents the number of clients.
   *
   * This variable holds the number of clients connected.
   * It is initialized to -1, indicating no clients are connected by default.
   */
  int numClient{-1};
};
} // namespace entity
#endif // ENTITY_HPP
