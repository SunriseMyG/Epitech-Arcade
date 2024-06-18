/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** testReturns84WhenArgcNot2
*/

#include "copy_main.cpp"

int main() {
    const char* argv[] = {"./arcade"};
    if (copy_main(1, argv) != 84) {
        return 1;
    }
    return 0;
}