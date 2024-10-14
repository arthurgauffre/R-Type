/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParentComponent
*/

#include <components/ParentComponent.hpp>

/**
 * @brief Constructs a new ParentComponent object.
 *
 * @param entityID The ID of the entity associated with this component.
 */
component::ParentComponent::ParentComponent(uint32_t entityID,
                                            uint32_t parentID)
    : AComponent(entityID), _parentID(parentID) {}

/**
 * @brief Destructor for the ParentComponent class.
 *
 * This destructor is responsible for cleaning up any resources
 * or performing any necessary finalization tasks when a
 * ParentComponent object is destroyed.
 */
component::ParentComponent::~ParentComponent() {}

/**
 * @brief Sets the parent ID for the component.
 *
 * This function assigns the given parent ID to the component's internal
 * _parentID member variable.
 *
 * @param parentID The ID of the parent to be set.
 */
void component::ParentComponent::setParentID(uint32_t parentID) {
  this->_parentID = parentID;
}

/**
 * @brief Retrieves the parent ID of the component.
 *
 * This function returns the ID of the parent component associated with this
 * instance.
 *
 * @return uint32_t The ID of the parent component.
 */
uint32_t component::ParentComponent::getParentID() { return this->_parentID; }