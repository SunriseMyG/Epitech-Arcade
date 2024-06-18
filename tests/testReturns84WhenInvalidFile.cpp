/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** testReturns84WhenInvalidFile
*/

#include "copy_main.cpp"

int main() {
    const char* argv[] = {"./arcade", "./lib/arcade_snake.so"};
    if (copy_main(2, argv) != 84) {
        return 1;
    }
    return 0;
}