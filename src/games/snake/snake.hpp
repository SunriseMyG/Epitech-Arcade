/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** snake
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include "../IGames.hpp"
    #include <iostream>
    #include <vector>
    #include <string>
    #include <list>
    #include <ctime>
    #include <cstdlib>
    #include <map>

    class Snake : public IGames {
        public:
            Snake() = default;
            ~Snake() = default;
            void init();
            void stop();
            void reset();

            void inputs(e_key key);

            const std::string &getName() const;
            const int &getScore() const;
            const int &getLife() const;
            const int &getLevel() const;
            const std::map<char, std::pair<std::string, int>> &getSprite();
            const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &getText();
            //const int &getTimer() const;

            bool isInfinite();

            std::vector<std::string> getMap();
            void algorithm();
            void drawMap();
            void setMap();

            void generateFruit();

            //movement

            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();

            void gameOver();
        protected:
        private:
            //IGame variables
            std::string _name;
            int _score;
            int _life;
            int _level;
            std::vector<std::string> _map;
            bool _infinite;
            std::map<char, std::pair<std::string, int>> _Sprite;
            std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> _Text;

            //Snake variables
            enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
            bool _gameOver;
            int _width;
            int _height;
            int _x;
            int _y;
            int _fruitX;
            int _fruitY;
            int _nTail;
            std::vector<int> _tailX;
            std::vector<int> _tailY;
            eDirection _dir;
    };
#endif /* !SNAKE_HPP_ */