/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** parsingErrors
*/

#include "parsingErrors.hpp"

ParsingErrors::ParsingErrors(const std::string &message, std::ostream &os)
    : Error(message, os)
{
    std::cerr << "Parsing error: " << message << std::endl;
}

ParsingErrors::~ParsingErrors(void) throw()
{
}