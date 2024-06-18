/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** DirManager
*/

#include "DirManager.hpp"

DirManager::DirManager()
{
}

const std::vector<std::string> DirManager::readDir(const std::string &dir)
{
    std::vector<std::string> files;

    for (const auto &entry : std::filesystem::directory_iterator(dir)) {
        files.push_back(entry.path());
    }

    return files;
}
