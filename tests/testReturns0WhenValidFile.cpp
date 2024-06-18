/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** testReturns0WhenValidFile
*/

#include "copy_main.cpp"

int main() {
    const char* argv[] = {"./arcade", "./lib/arcade_sfml.so"};
    if (copy_main(2, argv) != 0) {
        return 1;
    }
    return 0;
}