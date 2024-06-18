/*
** EPITECH PROJECT, 2024
** $
** File description:
** bootstrap
*/

#ifndef BOOTSTRAP_HPP_
    #define BOOTSTRAP_HPP_

    #include <iostream>
    #include <dlfcn.h>
    #include <string>
    #include <unistd.h>

    namespace Arcade {
        class LibLoader {
            public:
                LibLoader();
                ~LibLoader() = default;
                void loadLib(const std::string &libPath);
                void closeLib();
                void *getLib() const;
                void *getFunction(const std::string &functionName);
                bool checkFunction(const std::string &functionName);
            private:
                void *_lib;
        };
    }

#endif /* !BOOTSTRAP_HPP_ */
