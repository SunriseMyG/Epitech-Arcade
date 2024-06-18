/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

extern "C" IGames *entryPointGame()
{
    return new Nibbler();
}

void Nibbler::init()
{
    _name = "Nibbler";
    _score = 0;
    _life = 1;
    _level = 1;
    _gameOver = false;
    _infinite = true;
    _dir = eDirection::STOP;
    _map = {
        "XXXXXXXXXXXXXXXXX",
        "X F   F   F   F X",
        "XFXXXX X X XXXXFX",
        "X   F  X X  F   X",
        "X XXX XX XX XXX X",
        "X X X F   F X X X",
        "X XXX XXXXX XXX X",
        "XF F         F FX",
        "XX XXXXXFXXXXX XX",
        "X  F         F  X",
        "X XXXXXX XXXXXX X",
        "X F    X X    F X",
        "X XXXX  F  XXXX X",
        "X    X     X    X",
        "XFXXF FX XF FXXFX",
        "XFXXXXXX XXXXXXFX",
        "X     ooooO     X",
        "XXXXXXXXXXXXXXXXX"
    };
    _snake.clear();
    for (std::size_t y = 0; y < _map.size(); ++y) {
        for (std::size_t x = 0; x < _map[y].size(); ++x) {
            if (_map[y][x] == 'O' || _map[y][x] == 'o') {
                _snake.push_front({x, y});
            }
        }
    }
    _Sprite = {
        {'X', {"./assets/wall.png", 0}},
        {'F', {"./assets/cherry.png", 0}},
        {'o', {"./assets/snake_body_right.png", 0}},
        {'O', {"./assets/snake_head_right.png", 0}}
    };
    _Text = {
        {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}},
        {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}},
        {"Level: " + std::to_string(_level), {10, 70}, {255, 255, 255}}
    };
}

void Nibbler::stop()
{
    _gameOver = true;
}

void Nibbler::reset()
{
    stop();
    init();
}

void Nibbler::winGame()
{
    // _level++,
    _snake.clear();
    _map = {
        "XXXXXXXXXXXXXXXXX",
        "X F   F   F   F X",
        "XFXXXX X X XXXXFX",
        "X   F  X X  F   X",
        "X XXX XX XX XXX X",
        "X X X F   F X X X",
        "X XXX XXXXX XXX X",
        "XF F         F FX",
        "XX XXXXXFXXXXX XX",
        "X  F         F  X",
        "X XXXXXX XXXXXX X",
        "X F    X X    F X",
        "X XXXX  F  XXXX X",
        "X    X     X    X",
        "XFXXF FX XF FXXFX",
        "XFXXXXXX XXXXXXFX",
        "X     ooooO     X",
        "XXXXXXXXXXXXXXXXX"
    };
    // _Text[2] = {"Level: " + std::to_string(_level), {10, 70}, {255, 255, 255}};
    for (std::size_t y = 0; y < _map.size(); ++y) {
        for (std::size_t x = 0; x < _map[y].size(); ++x) {
            if (_map[y][x] == 'O' || _map[y][x] == 'o') {
                _snake.push_front({x, y});
            }
        }
    }
}

const std::string &Nibbler::getName() const
{
    return _name;
}

const int &Nibbler::getScore() const
{
    return _score;
}

const int &Nibbler::getLife() const
{
    return _life;
}

const int &Nibbler::getLevel() const
{
    return _level;
}

std::vector<std::string> Nibbler::getMap()
{
    return _map;
}

const std::map<char, std::pair<std::string, int>> &Nibbler::getSprite()
{
    return _Sprite;
}

const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &Nibbler::getText()
{
    return _Text;
}

bool Nibbler::isInfinite()
{
    return _infinite;
}

void Nibbler::moveUp()
{
    _dir = UP;
    Nibbler::algorithm();
}

void Nibbler::moveDown()
{
    _dir = DOWN;
    Nibbler::algorithm();
}

void Nibbler::moveLeft()
{
    _dir = LEFT;
    Nibbler::algorithm();
}

void Nibbler::moveRight()
{
    _dir = RIGHT;
    Nibbler::algorithm();
}

void Nibbler::inputs(e_key key)
{
    if (_gameOver) {
        _gameOver = false;
        init();
    }
    if (key == e_key::Z) {
        _Sprite['O'] = {"./assets/snake_head_up.png", 0};
        moveUp();
    } else if (key == e_key::S) {
        _Sprite['O'] = {"./assets/snake_head_down.png", 0};
        moveDown();
    } else if (key == e_key::Q) {
        _Sprite['O'] = {"./assets/snake_head_left.png", 0};
        moveLeft();
    } else if (key == e_key::D) {
        _Sprite['O'] = {"./assets/snake_head_right.png", 0};
        moveRight();
    }
}

void Nibbler::algorithm()
{
    if (_gameOver)
        return;
    std::pair<int, int> head = _snake.front();
    std::pair<int, int> tail = _snake.back();
    std::pair<int, int> newHead = head;
    switch (_dir) {
        case UP:
            newHead.second -= 1;
            break;
        case DOWN:
            newHead.second += 1;
            break;
        case LEFT:
            newHead.first -= 1;
            break;
        case RIGHT:
            newHead.first += 1;
            break;
        default:
            break;
    }
    if (_map[newHead.second][newHead.first] == 'X') {
        return;
    }
    if (_map[newHead.second][newHead.first] == 'F') {
        _score += 10;
        _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        _map[newHead.second][newHead.first] = ' ';
        _snake.push_front(newHead);

        // Vérifiez s'il reste des fruits sur la carte
        bool hasFruits = false;
        for (const auto &row : _map) {
            if (row.find('F') != std::string::npos) {
                hasFruits = true;
                break;
            }
        }
        // S'il n'y a plus de fruits, réinitialisez le jeu et augmentez le niveau
        if (!hasFruits) {
            _level++;
            _Text[2] = {"Level: " + std::to_string(_level), {10, 70}, {255, 255, 255}};
            winGame();
            return;
        }
    } else if (_map[newHead.second][newHead.first] == 'o') {
        _score += 10;
        _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        _map[newHead.second][newHead.first] = ' ';
        _snake.push_front(newHead);
        _map[tail.second][tail.first] = ' ';
        _snake.pop_back();
    } else {
        _snake.push_front(newHead);
        _map[tail.second][tail.first] = ' ';
        _snake.pop_back();
    }
    if (_snake.front() == _snake.back()) {
        _score += 10;
        _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        _map[tail.second][tail.first] = ' ';
        _snake.push_back(tail);
    }

    auto it = _snake.begin();
    it++;
    for (; it != _snake.end(); it++) {
        if (*it == newHead) {
            reset();
            return;
        }
    }

    _map[head.second][head.first] = ' ';
    _map[newHead.second][newHead.first] = 'O';

    it = _snake.begin();
    it++;
    for (; it != _snake.end(); it++) {
        _map[it->second][it->first] = 'o';
    }
}