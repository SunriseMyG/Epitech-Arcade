/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** DirManager
*/

#ifndef DirManager_HPP_
#define DirManager_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>

class DirManager {
    public:
        DirManager();
        ~DirManager() = default;
        const std::vector<std::string> readDir(const std::string &dir);
    private:
};

#endif /* !DirManager_HPP_ */
