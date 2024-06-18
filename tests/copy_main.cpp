/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** copy_main
*/

#include "../src/cores/libloader/libloader.cpp"
#include "../src/cores/errors/error.cpp"
#include "../src/cores/parsing/parsingErrors.cpp"


int copy_main(int argc, const char **argv)
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

    return 0;
}
