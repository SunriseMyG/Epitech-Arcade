/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unistd.h>
#include "../keys.hpp"

class IGames {
    public:
        IGames() = default;
        ~IGames() = default;
        virtual void init() = 0;
        virtual void stop() = 0;

        virtual void inputs(e_key key) = 0;

        virtual const std::string &getName() const = 0;  // return the name of the game
        virtual const int &getScore() const = 0;         // return the score of the player
        virtual const int &getLife() const = 0;          // return the life of the player
        virtual const int &getLevel() const = 0;         // return the level of the game

        virtual std::vector<std::string> getMap() = 0;   // return the map and the position of the enemies/player

        virtual bool isInfinite() = 0;                   // return if the game is infinite or not
        virtual const std::map<char, std::pair<std::string, int>> &getSprite() = 0; // return the sprite of the game
        virtual const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &getText() = 0; // return the text of the game
    protected:
        std::map<char, std::pair<std::string, int>> _Sprite;
        std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> _Text;
    private:
};

#endif /* !IGAMES_HPP_ */