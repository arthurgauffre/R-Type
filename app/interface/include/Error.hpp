/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <stdexcept>
#include <string>
#include <iostream>

#define NEW_EXCEPTION(name)                                                        \
    class name : public RtypeException                                                   \
    {                                                                                  \
    public:                                                                            \
        name(std::string const &message) noexcept     \
            : RtypeException(message) {}                                           \
    };

namespace rtype
{
    class RtypeException : public std::exception
    {
    public:
        RtypeException(std::string const &message) noexcept
            : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }
    private:
        std::string _message;
    };

    NEW_EXCEPTION(ServerException)
}

#endif /* !ERROR_HPP_ */
