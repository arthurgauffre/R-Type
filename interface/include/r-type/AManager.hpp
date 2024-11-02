/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AManager
*/

#pragma once
#include <r-type/IManager.hpp>

class AManager : virtual public IManager {
public:
  /**
   * @brief Default constructor for the AManager class.
   */
  AManager();

  /**
   * @brief Destructor for the AManager class.
   *
   * This destructor is responsible for cleaning up any resources
   * that the AManager class may have allocated during its lifetime.
   */
  ~AManager();

protected:
private:
};
