/*
** EPITECH PROJECT, 2024
** bootstrap [WSL : Ubuntu]
** File description:
** bootstrap
*/

#include "libloader.hpp"

Arcade::LibLoader::LibLoader()
{
}

void Arcade::LibLoader::loadLib(const std::string &libPath)
{
    _lib = dlopen(libPath.c_str(), RTLD_NOW);
    if (!_lib) {
        std::cerr << "Error: " << dlerror() << std::endl;
        exit(84);
    }
}

void Arcade::LibLoader::closeLib()
{
    dlclose(_lib);
}

void *Arcade::LibLoader::getLib() const
{
    return _lib;
}

void *Arcade::LibLoader::getFunction(const std::string &functionName)
{
    void *function = dlsym(_lib, functionName.c_str());
    if (!function) {
        std::cerr << "Error: " << dlerror() << std::endl;
        exit(84);
    }
    return function;
}

bool Arcade::LibLoader::checkFunction(const std::string &functionName)
{
    void *function = dlsym(_lib, functionName.c_str());
    if (!function) {
        return false;
    }
    return true;
}
