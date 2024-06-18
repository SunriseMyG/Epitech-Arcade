/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** snake
*/

#include "snake.hpp"

extern "C" IGames *entryPointGame()
{
    return new Snake();
}

void Snake::init()
{
    _name = "Snake";
    _score = 0;
    _life = 1;
    _level = 1;
    _infinite = true;
    _width = 20;
    _height = 20;
    _gameOver = false;
    _dir = STOP;
    _x = _width / 2;
    _y = _height / 2;
    _fruitX = rand() % _width;
    _fruitY = rand() % _height;
    _score = 0;
    _nTail = 4;

    _tailX.resize(_nTail);
    _tailY.resize(_nTail);

    for (int i = 0; i < _nTail; i++) {
        _tailX[i] = _x - i - 1;
        _tailY[i] = _y;
    }

    srand(time(NULL));
    _tailX.clear();
    _tailY.clear();
    _tailX.resize(100);
    _tailY.resize(100);

    std::string border(_width, '#');
    std::string inner = "#" + std::string(_width - 2, ' ') + "#";
    _map.clear();
    _map.push_back(border);
    for(int i = 0; i < _height - 2; i++) {
        _map.push_back(inner);
    }
    _map.push_back(border);

    _Sprite = {
        {'#', {"./assets/wall.png", 0}},
        {'F', {"./assets/apple.png", 0}},
        {'O', {"./assets/snake_head_right.png", 0}},
        {'o', {"./assets/snake_body_right.png", 0}},
    };
    _Text = {
        {"Score: 0", {0, 0}, {255, 255, 255}},
    };
}

void Snake::stop()
{
}

void Snake::reset()
{
    init();
}

void Snake::moveUp()
{
    _dir = UP;
    Snake::algorithm();
}

void Snake::inputs(e_key key)
{
    switch (key) {
    case e_key::Z:
        Snake::moveUp();
        _Sprite['O'] = {"./assets/snake_head_up.png", 0};
        break;
    case e_key::S:
        Snake::moveDown();
        _Sprite['O'] = {"./assets/snake_head_down.png", 0};
        break;
    case e_key::Q:
        Snake::moveLeft();
        _Sprite['O'] = {"./assets/snake_head_left.png", 0};
        break;
    case e_key::D:
        Snake::moveRight();
        _Sprite['O'] = {"./assets/snake_head_right.png", 0};
        break;
    case e_key::LEFT:
        Snake::moveLeft();
        _Sprite['O'] = {"./assets/snake_head_left.png", 0};
        break;
    case e_key::RIGHT:
        Snake::moveRight();
        _Sprite['O'] = {"./assets/snake_head_right.png", 0};
        break;
    case e_key::UP:
        Snake::moveUp();
        _Sprite['O'] = {"./assets/snake_head_up.png", 0};
        break;
    case e_key::DOWN:
        Snake::moveDown();
        _Sprite['O'] = {"./assets/snake_head_down.png", 0};
        break;
    default:
        break;
    }
}

void Snake::moveDown()
{
    _dir = DOWN;
    Snake::algorithm();
}

void Snake::moveLeft()
{
    _dir = LEFT;
    Snake::algorithm();
}

void Snake::moveRight()
{
    _dir = RIGHT;
    Snake::algorithm();
}

const std::string &Snake::getName() const
{
    return _name;
}

const int &Snake::getScore() const
{
    return _score;
}

const int &Snake::getLife() const
{
    return _life;
}

const int &Snake::getLevel() const
{
    return _level;
}

const std::map<char, std::pair<std::string, int>> &Snake::getSprite()
{
    return _Sprite;
}

const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &Snake::getText()
{
    return _Text;
}

std::vector<std::string> Snake::getMap()
{
    return _map;
}

void Snake::generateFruit()
{
    while (true) {
        _fruitX = rand() % (_width - 2) + 1;
        _fruitY = rand() % (_height - 2) + 1;

        bool isOnSnake = false;
        for (int i = 0; i < _nTail; i++) {
            if (_tailX[i] == _fruitX && _tailY[i] == _fruitY) {
                isOnSnake = true;
                break;
            }
        }

        if (!isOnSnake) {
            break;
        }
    }
}

void Snake::gameOver()
{
    _gameOver = true;
    _life = 0;
    _Text[0] = {"Game Over", {0, 0}, {255, 255, 255}};
}

void Snake::algorithm()
{
    if (!_gameOver) {
        int prevX = _tailX[0];
        int prevY = _tailY[0];
        int prev2X, prev2Y;
        _tailX[0] = _x;
        _tailY[0] = _y;

        for (int i = 1; i < _nTail; i++) {
            prev2X = _tailX[i];
            prev2Y = _tailY[i];
            _tailX[i] = prevX;
            _tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (_dir) {
        case LEFT:
            _x--;
            break;
        case RIGHT:
            _x++;
            break;
        case UP:
            _y--;
            break;
        case DOWN:
            _y++;
            break;
        default:
            break;
        }

        if (_x >= _width)
            _x = 0;
        else if (_x < 0)
            _x = _width - 1;
        if (_y >= _height)
            _y = 0;
        else if (_y < 0)
            _y = _height - 1;

        if (_map[_y][_x] == 'F') {
            _score += 10;
            Snake::generateFruit();
            _nTail++;
            if (!_Text.empty()) {
                _Text[0] = {"Score: " + std::to_string(_score), {0, 0}, {255, 255, 255}};
            }
        }

        if (_map[_y][_x] == '#') {
            gameOver();
        }

        for (int i = 0; i < _nTail; i++) {
            if (_map[_y][_x] == 'o') {
                gameOver();
            }
        }
        Snake::setMap();
        // Snake::drawMap();
    } else {
        sleep(1);
        reset();
    }
    //for qui augmente le score
    // for (int i = 0; i < 10; i++) {
    //     _score++;
    //     if (!_Text.empty())
    //         _Text[0] = {"Score: " + std::to_string(_score), {0, 0}, {255, 255, 255}};
    // }
}

void Snake::setMap()
{
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (i == 0 || i == _height - 1 || j == 0 || j == _width - 1)
                _map[i][j] = '#';
            else
                _map[i][j] = ' ';
        }
    }

    _map[_y][_x] = 'O';

    _map[_fruitY][_fruitX] = 'F';

    for (int i = 0; i < _nTail; i++) {
        _map[_tailY[i]][_tailX[i]] = 'o';
    }
}

void Snake::drawMap()
{
    for (size_t i = 0; i < _map.size() + 1; i++) {
        if (i % _width == 0)
            std::cout << std::endl;

        std::cout << _map[i];
    }
}

bool Snake::isInfinite()
{
    return _infinite;
}