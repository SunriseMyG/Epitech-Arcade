/*
** EPITECH PROJECT, 2024
** bootstrap [WSL : Ubuntu]
** File description:
** error
*/

#include "error.hpp"

Error::Error(const std::string &message, std::ostream &os) : _message(message), _os(os)
{
}

const char *Error::what() const throw()
{
    _os << _message << std::endl;
    return _message.c_str();
}
