/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>
#include <stdexcept>
#include <string>

#define NEW_EXCEPTION(name)                                                    \
  class name : public RtypeException {                                         \
  public:                                                                      \
    name(std::string const &message) noexcept : RtypeException(message) {}     \
  };

namespace rtype {
class RtypeException : public std::exception {
public:
  /**
   * @brief Constructs a new RtypeException object with the given message.
   *
   * @param message The error message associated with the exception.
   */
  RtypeException(std::string const &message) noexcept : _message(message) {}

  /**
   * @brief Returns the explanatory string.
   *
   * This function overrides the what() method from the std::exception class.
   * It provides a description of the error that occurred.
   *
   * @return A C-style string containing the error message.
   */
  const char *what() const noexcept override { return _message.c_str(); }

private:
  /**
   * @brief A string that holds the error message.
   */
  std::string _message;
};

NEW_EXCEPTION(ServerException)
NEW_EXCEPTION(ClientConnectionException)
NEW_EXCEPTION(GameLoosed)
NEW_EXCEPTION(GameWon)
} // namespace rtype

#endif /* !ERROR_HPP_ */
