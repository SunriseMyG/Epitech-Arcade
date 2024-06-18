/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** pacman
*/

class AIPacman;

#include "../IGames.hpp"
#include <chrono>

#ifndef PACMAN_HPP_
    #define PACMAN_HPP_

    class Pacman : public IGames {
        public:
            struct Position {
                size_t x;
                size_t y;
            };
            Pacman();
            ~Pacman() = default;
            void init();
            void stop();
            void win();
            const std::string &getName() const;
            const int &getScore() const;
            const int &getLife() const;
            const int &getLevel() const;
            const std::map<char, std::pair<std::string, int>> &getSprite();

            const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &getText();
            int getPoint();
            Position getPosition();
            bool eatDot();
            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();
            std::vector<std::string> getMap();
            void algorithm();
            bool checkDotsLeft();
            void inputs(e_key key);
            bool isInfinite();
            void reset();
            void resetPosition();
            void reduceLife();
        protected:
            std::vector<std::string> _map;
        private:
            std::string _name;
            int _score;
            int _life;
            int _level;
            bool _gameOver;
            bool _infinite;
            Position _pos;
            enum eDirection
            {
                STOP = 0,
                LEFT,
                RIGHT,
                UP,
                DOWN
            };
            eDirection dir;
            bool _ghostsSpawned = false;
            std::chrono::time_point<std::chrono::steady_clock> _start;
            std::vector<AIPacman*> _ghosts;
            bool vulnerable;
            bool _animation;
            int _powerUpMoves;
            int _timeToSpawnGhost;
            std::map<char, std::pair<std::string, int>> _Sprite;
            std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> _Text;
    };

#endif /* !PACMAN_HPP_ */
