/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine [WSL : Ubuntu]
** File description:
** AIPacman
*/

#include "Pacman.hpp"
#include <cstdlib>
#include <vector>

#ifndef AIPACMAN_HPP_
    #define AIPACMAN_HPP_

    class AIPacman : public Pacman {
        public:
            AIPacman(size_t x, size_t y);
            virtual ~AIPacman() = default;

            void initGame();
            void move(std::vector<std::string> &map);
            Position getPosition();
            bool isValidMove(Position pos);
            void resetPosition();
            void setSpawnPosition(size_t x, size_t y);

        protected:
        private:
            Position _spawnPosiion;
            char casevalue;
            Position _pos;
    };

#endif /* !AIPACMAN_HPP_ */
