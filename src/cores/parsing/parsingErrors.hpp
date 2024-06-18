/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** parsingErrors
*/

#include "../errors/error.hpp"

#ifndef PARSINGERRORS_HPP_
    #define PARSINGERRORS_HPP_

    class ParsingErrors : public Error {
        public:
            ParsingErrors(const std::string &message, std::ostream &os);
            ~ParsingErrors(void) throw();
    };

#endif /* !PARSINGERRORS_HPP_ */
