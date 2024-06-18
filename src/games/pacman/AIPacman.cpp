/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine [WSL : Ubuntu]
** File description:
** ia_pacman
*/

#include "AIPacman.hpp"

/**
* Constructor for AIPacman class.
* 
* @param None
*
* @return None
*  
* @throws None
*/
AIPacman::AIPacman(size_t x, size_t y) : _pos{x, y}
{
}

/**
* Initializes the game by finding the starting position on the map and moving the player there.
* 
* @param None
*
* @return None
*
* @throws None
*/
void AIPacman::initGame()
{
    //print the positon of the AI Pacman
    // printf("%ld, %ld\n", _pos.x, _pos.y);
    casevalue = ' ';
}

/**
* Get the position of the AI Pacman.
*
* @param None
*
* @return The position of the AI Pacman.
*
* @throws None
*/
AIPacman::Position AIPacman::getPosition()
{
    return _pos;
}

/**
* Move the AI Pacman using a modulo 4 by a random number.
*
* @param std::vector<std::string> &map
*
* @return None
*
* @throws None
*/
void AIPacman::move(std::vector<std::string> &map)
{
    int direction = rand() % 4;

    switch (direction) {
        case 0:
            // printf("Move right\n");
            if (map[_pos.y][_pos.x + 1] != 'X' && map[_pos.y][_pos.x + 1] != 'E') {
                map[_pos.y][_pos.x] = casevalue;
                casevalue = map[_pos.y][_pos.x + 1];
                map[_pos.y][_pos.x + 1] = 'E';
                _pos.x++;
                if (_pos.x == Pacman::getPosition().x && _pos.y == Pacman::getPosition().y) {
                    Pacman::reduceLife();
                    if (Pacman::getLife() > 0) {
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = ' ';
                        Pacman::resetPosition();
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = 'P';
                    }
                    else
                        Pacman::reset();
                }
            } else {
                if (map[_pos.y][_pos.x + 1] != 'X' && map[_pos.y][_pos.x + 1] != 'E'
                && map[_pos.y][_pos.x - 1] != 'X' && map[_pos.y][_pos.x - 1] != 'E'
                && map[_pos.y + 1][_pos.x] != 'X' && map[_pos.y + 1][_pos.x] != 'E'
                && map[_pos.y - 1][_pos.x] != 'X' && map[_pos.y - 1][_pos.x] != 'E') {
                    move(map);
                }
            }
            break;
        case 1:
            // printf("Move left\n");
            if (map[_pos.y][_pos.x - 1] != 'X' && map[_pos.y][_pos.x - 1] != 'E') {
                map[_pos.y][_pos.x] = casevalue;
                casevalue = map[_pos.y][_pos.x - 1];
                map[_pos.y][_pos.x - 1] = 'E';
                _pos.x--;
                if (_pos.x == Pacman::getPosition().x && _pos.y == Pacman::getPosition().y) {
                    Pacman::reduceLife();
                    if (Pacman::getLife() > 0) {
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = ' ';
                        Pacman::resetPosition();
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = 'P';
                    }
                    else
                        Pacman::reset();
                }
            } else {
                if (map[_pos.y][_pos.x + 1] != 'X' && map[_pos.y][_pos.x + 1] != 'E'
                && map[_pos.y][_pos.x - 1] != 'X' && map[_pos.y][_pos.x - 1] != 'E'
                && map[_pos.y + 1][_pos.x] != 'X' && map[_pos.y + 1][_pos.x] != 'E'
                && map[_pos.y - 1][_pos.x] != 'X' && map[_pos.y - 1][_pos.x] != 'E') {
                    move(map);
                }
            }
            break;
        case 2:
            // printf("Move down\n");
            if (map[_pos.y + 1][_pos.x] != 'X' && map[_pos.y + 1][_pos.x] != 'E') {
                casevalue = map[_pos.y + 1][_pos.x];
                map[_pos.y][_pos.x] = casevalue;
                map[_pos.y + 1][_pos.x] = 'E';
                _pos.y++;
                if (_pos.x == Pacman::getPosition().x && _pos.y == Pacman::getPosition().y) {
                    Pacman::reduceLife();
                    if (Pacman::getLife() > 0) {
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = ' ';
                        Pacman::resetPosition();
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = 'P';
                    }
                    else
                        Pacman::reset();
                }
            } else {
                if (map[_pos.y][_pos.x + 1] != 'X' && map[_pos.y][_pos.x + 1] != 'E'
                && map[_pos.y][_pos.x - 1] != 'X' && map[_pos.y][_pos.x - 1] != 'E'
                && map[_pos.y + 1][_pos.x] != 'X' && map[_pos.y + 1][_pos.x] != 'E'
                && map[_pos.y - 1][_pos.x] != 'X' && map[_pos.y - 1][_pos.x] != 'E') {
                    move(map);
                }
            }
            break;
        case 3:
            // printf("Move up\n");
            if (map[_pos.y - 1][_pos.x] != 'X' && map[_pos.y - 1][_pos.x] != 'E') {
                casevalue = map[_pos.y - 1][_pos.x];
                map[_pos.y][_pos.x] = casevalue;
                map[_pos.y - 1][_pos.x] = 'E';
                _pos.y--;
                if (_pos.x == Pacman::getPosition().x && _pos.y == Pacman::getPosition().y) {
                    Pacman::reduceLife();
                    if (Pacman::getLife() > 0) {
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = ' ';
                        Pacman::resetPosition();
                        printf("%ld, %ld\n", Pacman::getPosition().x, Pacman::getPosition().y);
                        map[Pacman::getPosition().y][Pacman::getPosition().x] = 'P';
                    }
                    else
                        Pacman::reset();
                }
            } else {
                if (map[_pos.y][_pos.x + 1] != 'X' && map[_pos.y][_pos.x + 1] != 'E'
                && map[_pos.y][_pos.x - 1] != 'X' && map[_pos.y][_pos.x - 1] != 'E'
                && map[_pos.y + 1][_pos.x] != 'X' && map[_pos.y + 1][_pos.x] != 'E'
                && map[_pos.y - 1][_pos.x] != 'X' && map[_pos.y - 1][_pos.x] != 'E') {
                    move(map);
                }
            }
            break;
    }
}

/**
* Function that set the position of the AI Pacman to his spawn position.
* 
* @param None
* 
* @return None
* 
* @throws None
**/
void AIPacman::resetPosition()
{
    _pos = _spawnPosiion;
}

/**
* Set the spawn position of the AI Pacman.
* 
* @param size_t x
* 
* @param size_t y
* 
* @return None
* 
* @throws None
**/
void AIPacman::setSpawnPosition(size_t x, size_t y)
{
    _spawnPosiion = {x, y};
}

/**
* Check if the AI can move or not.
*
* @param newPos The new position of the AI Pacman.
*
* @return None
*
* @throws None
*/
bool AIPacman::isValidMove(Position newPos)
{
    if (newPos.x >= _map[0].size() || newPos.y >= _map.size())
        return false;
    if (_map[newPos.y][newPos.x] == 'X')
        return false;
    return true;
}
