/*
** EPITECH PROJECT, 2024
** bootstrap [WSL : Ubuntu]
** File description:
** main
*/

#include "Core.hpp"
#include "../lib/IGraphics.hpp"
#include "../lib/SDL2/SDL.hpp"
#include "../lib/NCurses/Ncurse.hpp"
#include "./launcher/launcher.hpp"
#include "./libloader/libloader.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    if (access(argv[1], F_OK) == -1) {
        ParsingErrors("File not found", std::cerr);
        return 84;
    }
    auto filename = std::string(argv[1]);

    Arcade::LibLoader libLoader;
    libLoader.loadLib(filename);
    if (!libLoader.checkFunction("entryPointGraph")) {
        ParsingErrors("Invalid file", std::cerr);
        libLoader.closeLib();
        return 84;
    }
    libLoader.closeLib();

    Arcade::Core core;
    Launcher launcher;
    launcher.setCore(&core);
    core.init(filename);
    core.switchAll(&launcher, core.LoadGraph(filename));
    return 0;
}
