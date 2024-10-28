/*
** EPITECH PROJECT, 2024
** *
** File description:
** IEntity
*/

#pragma once
#include <cstdint>

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
  protected:
    EntityCommunication communicationStatus{EntityCommunication::CREATE};
};
} // namespace entity
