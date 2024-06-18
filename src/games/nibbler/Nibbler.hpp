/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** Nibbler
*/


#include "../IGames.hpp"
#include <deque>

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_

    class Nibbler : public IGames {
        public:
            Nibbler() = default;
            ~Nibbler() = default;

            void init();
            void stop();
            void win();
            void reset();
            void inputs(e_key key);
            void winGame();

            const std::string &getName() const;
            const int &getScore() const;
            const int &getLife() const;
            const int &getLevel() const;

            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();

            std::vector<std::string> getMap();

            bool isInfinite();
            const std::map<char, std::pair<std::string, int>> &getSprite();
            const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &getText();
            void algorithm();
        protected:
            std::string _name;
            int _score;
            int _life;
            int _level;
            bool _gameOver;
            bool _infinite;
            std::vector<std::string> _map;
            enum eDirection
            {
                STOP = 0,
                LEFT,
                RIGHT,
                UP,
                DOWN
            };
            eDirection _dir;
            std::map<char, std::pair<std::string, int>> _Sprite;
            std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> _Text;
            std::deque<std::pair<int, int>> _snake;
        private:
    };

#endif /* !NIBBLER_HPP_ */
