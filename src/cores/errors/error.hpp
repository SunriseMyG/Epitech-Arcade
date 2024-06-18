/*
** EPITECH PROJECT, 2024
** bootstrap [WSL : Ubuntu]
** File description:
** error
*/

#include <iostream>
#include <exception>
#include <string>

#ifndef ERROR_HPP_
    #define ERROR_HPP_

    class Error : public std::exception {
        public:
            Error(const std::string &message, std::ostream &os);
            ~Error() = default;
            const char *what() const throw() override;
        protected:
            std::string _message;
            std::ostream &_os;
    };

#endif /* !ERROR_HPP_ */
