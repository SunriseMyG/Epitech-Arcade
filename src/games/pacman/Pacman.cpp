/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** pacman
*/

#include "Pacman.hpp"
#include "AIPacman.hpp"

/**
* Entry point for the Pacman game.
* 
* @param None
* 
* @return IGames object representing the Pacman game.
* 
* @throws None
*/
extern "C" IGames *entryPointGame()
{
    return new Pacman();
}

/**
* Constructor for the Pacman class.
*
* @param None
*
* @return None
*
* @throws None
*/
Pacman::Pacman() : _name("Pacman"), _score(0)
{

}

/**
* Function that stop the game by setting the _gameOver at True
* 
* @param None
* 
* @return None
* 
* @throws None
* 
**/
void Pacman::stop()
{
    std::cout << "Score: " << getScore() << std::endl;
    _gameOver = true;
    std::cout << "Pacman game is stopped" << std::endl;
    std::cout << "Level: " << _level << std::endl;
}

/**
* Initializes the Pacman game by setting up the game environment, including the name, score, game over status, lives, and map.
*
* @param None
* 
* @return None
*
* @throws None
*/
void Pacman::init()
{
    _name = "Pacman";
    _score = 0;
    _gameOver = false;
    _life = 3;
    _level = 1;
    _start = std::chrono::steady_clock::now();
    _ghostsSpawned = false;
    _timeToSpawnGhost = 0;
    vulnerable = false;
    _powerUpMoves = 0;
    _infinite = true;
    _map = {
        "XXXXXXXXXXXXXXXXXXXXX",
        "X.........X.........X",
        "X.XXX.XXX.X.XXX.XXX.X",
        "XFX X.X X.X.X X.X XFX",
        "X.XXX.XXX.X.XXX.XXX.X",
        "X...................X",
        "X.XXX.X.XXXXX.X.XXX.X",
        "X.XXX.X.XXXXX.X.XXX.X",
        "X.....X...X...X.....X",
        "XXXXX.XXX X XXX.XXXXX",
        "    X.X       X.X    ",
        "    X.X XX XX X.X    ",
        "XXXXX.X XE EX X.XXXXX",
        "X    .  XE EX  .    X",
        "XXXXX.X XXXXX X.XXXXX",
        "    X.X       X.X    ",
        "    X.X XXXXX X.X    ",
        "XXXXX.X XXXXX X.XXXXX",
        "X.........X.........X",
        "X.XXX.XXX.X.XXX.XXX.X",
        "XF..X..... .....X..FX",
        "XXX.X.X.XXXXX.X.X.XXX",
        "XXX.X.X.XXXXX.X.X.XXX",
        "X.....X...X...X.....X",
        "X.XXXXXXX.X.XXXXXXX.X",
        "X.........P.........X",
        "XXXXXXXXXXXXXXXXXXXXX"};
    _Sprite = {
        {'X', std::make_pair("assets/wall.png", 0)},
        {'.', std::make_pair("assets/pacgum.png", 0)},
        {'F', std::make_pair("assets/apple.png", 0)},
        {'P', std::make_pair("assets/pacman_right.png", 0)},
        {'E', std::make_pair("assets/pacman_enemy.png", 0)}
    };
    _Text = {
        {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}},
        {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}},
        {"Level: " + std::to_string(_level), {10, 70}, {255, 255, 255}},
    };

    _animation = false;

    //init and get the position of the player
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'P') {
                _pos = {x, y};
                //print pos
                // std::cout << "Pacman position: " << _pos.x << " " << _pos.y << std::endl;
            }
        }
    }
    //init ghost in game
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'E') {
                AIPacman *ghost = new AIPacman(x, y);
                ghost->setSpawnPosition(x, y);
                //print the position of the ghost
                // std::cout << "Ghost position: " << ghost->getPosition().x << " " << ghost->getPosition().y << std::endl;
                ghost->initGame();
                _ghosts.push_back(ghost);
            }
        }
    }
    // std::cout << "Pacman game is initialized" << std::endl;
}

/**
* Function that reset the game by calling stop and init function
* 
* @param None
* 
* @return None
* 
* @throws None
* 
**/
void Pacman::reset() {
    stop();
    init();
}

/**
* Function that reset the game for the win and increment the score / level
* 
* @param None
* 
* @return None
* 
* @throws None
*
**/
void Pacman::win()
{
    _level++;
    _Text[2] = {"Level: " + std::to_string(_level), {10, 70}, {255, 255, 255}};
    _timeToSpawnGhost = 0;
    vulnerable = false;
    _powerUpMoves = 0;
    for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
        delete *it;
    }
    _ghosts.clear();
    _pos = {10, 25};
    _map = {
        "XXXXXXXXXXXXXXXXXXXXX",
        "X.........X.........X",
        "X.XXX.XXX.X.XXX.XXX.X",
        "XFX X.X X.X.X X.X XFX",
        "X.XXX.XXX.X.XXX.XXX.X",
        "X...................X",
        "X.XXX.X.XXXXX.X.XXX.X",
        "X.XXX.X.XXXXX.X.XXX.X",
        "X.....X...X...X.....X",
        "XXXXX.XXX X XXX.XXXXX",
        "    X.X       X.X    ",
        "    X.X XX XX X.X    ",
        "XXXXX.X XE EX X.XXXXX",
        "X    .  XE EX  .    X",
        "XXXXX.X XXXXX X.XXXXX",
        "    X.X       X.X    ",
        "    X.X XXXXX X.X    ",
        "XXXXX.X XXXXX X.XXXXX",
        "X.........X.........X",
        "X.XXX.XXX.X.XXX.XXX.X",
        "XF..X..... .....X..FX",
        "XXX.X.X.XXXXX.X.X.XXX",
        "XXX.X.X.XXXXX.X.X.XXX",
        "X.....X...X...X.....X",
        "X.XXXXXXX.X.XXXXXXX.X",
        "X...................X",
        "XXXXXXXXXXXXXXXXXXXXX"};
    _map[_pos.y][_pos.x] = 'P';
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'E') {
                AIPacman *ghost = new AIPacman(x, y);
                ghost->initGame();
                _ghosts.push_back(ghost);
            }
        }
    }
}

/**
* Function that return the table of the sprites
* 
* @param None
* 
* @return the table of the sprites
* 
* @throws None
* 
**/
const std::map<char, std::pair<std::string, int>> &Pacman::getSprite()
{
    return _Sprite;
}

/**
* Function that return the table of the text
* 
* @param None
* 
* @return the table of the text
* 
* @throws None
* 
**/
const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &Pacman::getText()
{
    return _Text;
}

/**
* Retrieves the score of Pacman.
*
* @param None
* 
* @return the score of Pacman
*
* @throws None
* 
*/
const int &Pacman::getScore() const
{
    return _score;
}

/**
* Retrieve the position of Pacman.
*
* @param None
* 
* @return Position object representing Pacman's position.
* 
* @throws None
* 
*/
Pacman::Position Pacman::getPosition()
{
    return _pos;
}

/**
* Get the current life of Pacman.
*
* @param None
* 
* @return the current life of Pacman
* 
* @throws None
* 
*/
const int &Pacman::getLife() const
{
    return _life;
}

/**
* Get the level of the Pacman.
*
* @param None
*
* @return the level of the Pacman
*
* @throws None
*/
const int &Pacman::getLevel() const
{
    return _level;
}

/**
* Get the name of the Pacman.
*
* @param None
*
* @return the name of the Pacman
*
* @throws None
*/
const std::string &Pacman::getName() const
{
    return _name;
}

/**
* Get the map of the Pacman.
*
* @param None
*
* @return the map of the Pacman
*
* @throws None
*/
std::vector<std::string> Pacman::getMap()
{
    return _map;
}

/**
* Check if there are any dots left on the game board.
* 
* @param None
* 
* @return true if there are dots left, false otherwise
* 
* @throws None
*/
bool Pacman::checkDotsLeft()
{
    for (const auto& row : _map) {
        if (row.find('.') != std::string::npos) {
            return true;
        }
    }
    return false;
}

/**
* Moves the Pacman character up on the game board if the cell above is not a wall.
*
* @param None
*
* @return None
*
* @throws None
*/
void Pacman::moveUp()
{
    dir = UP;
    if (_pos.y > 0 && _map[_pos.y - 1][_pos.x] != 'X') {
        if (_map[_pos.y - 1][_pos.x] == '.') {
            _score += 10;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        } else if (_map[_pos.y - 1][_pos.x] == 'E') {
            if (!vulnerable && _life > 0) {
                _life--;
                _Text[1] = {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}};
                if (_life == 0) {
                    stop();
                    sleep(1);
                    for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                        delete *it;
                    }
                    _ghosts.clear();
                    reset();
                    return;
                }
                _map[_pos.y][_pos.x] = ' ';
                _pos = {10, 25};
                _map[_pos.y][_pos.x] = 'P';
                return;
            } else if (vulnerable) {
                _score += 200;
                _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
                _map[_pos.y][_pos.x] = ' ';
                _pos.y--;
                _map[_pos.y][_pos.x] = 'P';
                for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                    if ((*it)->getPosition().x == _pos.x && (*it)->getPosition().y == _pos.y) {
                        // _ghosts.erase(it);
                        (*it)->resetPosition();
                        break;
                    }
                }
            }
        }
        if (_map[_pos.y - 1][_pos.x] == 'F') {
            _score += 50;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
            vulnerable = true;
            _powerUpMoves = 0;
        }
        _map[_pos.y][_pos.x] = ' ';
        _pos.y--;
        _map[_pos.y][_pos.x] = 'P';
        _timeToSpawnGhost++;
        if (vulnerable) {
            _powerUpMoves++;
            if (_powerUpMoves >= 23) {
                vulnerable = false;
            }
        }
    }
    Pacman::algorithm();
    if (!checkDotsLeft()) {
        win();
    }
}

/**
* Moves the Pacman character down on the game board if the cell above is not a wall.
*
* @param None
*
* @return None
*
* @throws None
*/
void Pacman::moveDown()
{
    dir = DOWN;
    if (_map[_pos.y + 1][_pos.x] != 'X') {
        if (_map[_pos.y + 1][_pos.x] == '.') {
            _score += 10;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        } else if (_map[_pos.y + 1][_pos.x] == 'E') {
            if (!vulnerable && _life > 0) {
                _life--;
                _Text[1] = {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}};
                if (_life == 0) {
                    stop();
                    sleep(1);
                    for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                        delete *it;
                    }
                    _ghosts.clear();
                    reset();
                    return;
                }
                _map[_pos.y][_pos.x] = ' ';
                _pos = {10, 25};
                _map[_pos.y][_pos.x] = 'P';
                return;
            } else if (vulnerable) {
                _score += 200;
                _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
                _map[_pos.y][_pos.x] = ' ';
                _pos.y++;
                _map[_pos.y][_pos.x] = 'P';
                for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                    if ((*it)->getPosition().x == _pos.x && (*it)->getPosition().y == _pos.y) {
                        // _ghosts.erase(it);
                        (*it)->resetPosition();
                        break;
                    }
                }
            }
        }
        if (_map[_pos.y + 1][_pos.x] == 'F') {
            _score += 50;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
            vulnerable = true;
            _powerUpMoves = 0;
        }
        _map[_pos.y][_pos.x] = ' ';
        _pos.y++;
        _map[_pos.y][_pos.x] = 'P';
        _timeToSpawnGhost++;
        if (vulnerable) {
            _powerUpMoves++;
            if (_powerUpMoves >= 23) {
                vulnerable = false;
            }
        }
    }
    Pacman::algorithm();
    if (!checkDotsLeft()) {
        win();
    }
}

/**
* Moves the Pacman character left on the game board if the cell above is not a wall.
*
* @param None
*
* @return None
*
* @throws None
*/
void Pacman::moveLeft()
{
    dir = LEFT;
    if (_map[_pos.y][_pos.x - 1] != 'X') {
        if (_map[_pos.y][_pos.x - 1] == '.') {
            _score += 10;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        } else if (_map[_pos.y][_pos.x - 1] == 'E') {
            if (!vulnerable && _life > 0) {
                _life--;
                _Text[1] = {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}};
                if (_life == 0) {
                    stop();
                    sleep(1);
                    for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                        delete *it;
                    }
                    _ghosts.clear();
                    reset();
                    return;
                }
                _map[_pos.y][_pos.x] = ' ';
                _pos = {10, 25};
                _map[_pos.y][_pos.x] = 'P';
                return;
            } else if (vulnerable) {
                _score += 200;
                _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
                _map[_pos.y][_pos.x] = ' ';
                _pos.x--;
                _map[_pos.y][_pos.x] = 'P';
                for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                    if ((*it)->getPosition().x == _pos.x && (*it)->getPosition().y == _pos.y) {
                        // _ghosts.erase(it);
                        (*it)->resetPosition();
                        break;
                    }
                }
            }
        }
        if (_map[_pos.y][_pos.x - 1] == 'F') {
            _score += 50;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
            vulnerable = true;
            _powerUpMoves = 0;
        }
        _map[_pos.y][_pos.x] = ' ';
        _pos.x--;
        _map[_pos.y][_pos.x] = 'P';
        _timeToSpawnGhost++;
        if (vulnerable) {
            _powerUpMoves++;
            if (_powerUpMoves >= 23) {
                vulnerable = false;
            }
        }
    }
    Pacman::algorithm();
    if (!checkDotsLeft()) {
        win();
    }
}

/**
* Moves the Pacman character right on the game board if the cell above is not a wall.
*
* @param None
*
* @return None
*
* @throws None
*/
void Pacman::moveRight()
{
    dir = RIGHT;
    if (_map[_pos.y][_pos.x + 1] != 'X') {
        if (_map[_pos.y][_pos.x + 1] == '.') {
            _score += 10;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
        }
        else if (_map[_pos.y][_pos.x + 1] == 'E') {
            if (!vulnerable && _life > 0) {
                _life--;
                _Text[1] = {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}};
                if (_life == 0) {
                    stop();
                    sleep(1);
                    for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                        delete *it;
                    }
                    _ghosts.clear();
                    reset();
                    return;
                }
                _map[_pos.y][_pos.x] = ' ';
                _pos = {10, 25};
                _map[_pos.y][_pos.x] = 'P';
                return;
            } else if (vulnerable) {
                _score += 200;
                _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
                _map[_pos.y][_pos.x] = ' ';
                _pos.x++;
                _map[_pos.y][_pos.x] = 'P';
                for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                    if ((*it)->getPosition().x == _pos.x && (*it)->getPosition().y == _pos.y) {
                        // _ghosts.erase(it);
                        (*it)->resetPosition();
                        break;
                    }
                }
            }
        }
        if (_map[_pos.y][_pos.x + 1] == 'F') {
            _score += 50;
            _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
            vulnerable = true;
            _powerUpMoves = 0;
        }
        _map[_pos.y][_pos.x] = ' ';
        _pos.x++;
        _map[_pos.y][_pos.x] = 'P';
        _timeToSpawnGhost++;
        if (vulnerable) {
            _powerUpMoves++;
            if (_powerUpMoves >= 23) {
                vulnerable = false;
            }
        }
    }
    Pacman::algorithm();
    if (!checkDotsLeft()) {
        win();
    }
}

/**
* A function that updates the game environment.
* 
* @param None
* 
* @return None
* 
* @throws None
* 
*/
void Pacman::algorithm()
{
    if (_timeToSpawnGhost >= 40) {
        for (size_t i = 0; i < _ghosts.size(); i++) {
            _ghosts[i]->move(_map);
            if (_ghosts[i]->getPosition().x == _pos.x && _ghosts[i]->getPosition().y == _pos.y) {
                if (!vulnerable && _life > 0) {
                    _life--;
                    _Text[1] = {"Life: " + std::to_string(_life), {10, 40}, {255, 255, 255}};
                    if (_life == 0) {
                        stop();
                        sleep(1);
                        for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                            delete *it;
                        }
                        _ghosts.clear();
                        reset();
                        return;
                    }
                    _map[_pos.y][_pos.x] = ' ';
                    _pos = {10, 25};
                    _map[_pos.y][_pos.x] = 'P';
                    return;
                } else if (vulnerable) {
                    _score += 200;
                    _Text[0] = {"Score: " + std::to_string(_score), {10, 10}, {255, 255, 255}};
                    _map[_pos.y][_pos.x] = ' ';
                    _pos = {10, 25};
                    _map[_pos.y][_pos.x] = 'P';
                    for (auto it = _ghosts.begin(); it != _ghosts.end(); it++) {
                        if ((*it)->getPosition().x == _pos.x && (*it)->getPosition().y == _pos.y) {
                            (*it)->resetPosition();
                            break;
                        }
                    }
                }
            }
            // std::cout << "Ghost position: " << _ghosts[i]->getPosition().x << " " << _ghosts[i]->getPosition().y << std::endl;
        }
    }
    // for (size_t y = 0; y < _map.size(); y++) {
    //     for (size_t x = 0; x < _map[y].size(); x++) {
    //         std::cout << _map[y][x];
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "Life: " << _life << std::endl;
}

/**
* Function that updates the game environment.
*
* @param None
*
* @return None
*
* @throws None
**/
bool Pacman::isInfinite()
{
    return _infinite;
}

/**
* Function that reset the position of the player
* 
* @param None
* 
* @return None
* 
* @throws None
* 
*
**/
void Pacman::resetPosition()
{
    _pos = {10, 25};
}

/**
* Function that reduce the life of the player
* 
* @param None
* 
* @return None
* 
* @throws None
* 
**/
void Pacman::reduceLife()
{
    _life--;
}

/**
* Function that manage input of the game
* 
* @param e_key key
* 
* @return None
* 
* @throws None
* 
**/
void Pacman::inputs(e_key key)
{
    if (vulnerable)
        _Sprite['E'] = std::make_pair("assets/pacman_enemy_vulnerable.png", 0);
    else
        _Sprite['E'] = std::make_pair("assets/pacman_enemy.png", 0);

    if (key == e_key::Z) {
        _Sprite['P'] = std::make_pair("assets/pacman_up.png", 0);
        moveUp();
    } else if (key == e_key::S) {
        _Sprite['P'] = std::make_pair("assets/pacman_down.png", 0);
        moveDown();
    } else if (key == e_key::Q) {
        _Sprite['P'] = std::make_pair("assets/pacman_left.png", 0);
        moveLeft();
    } else if (key == e_key::D) {
        _Sprite['P'] = std::make_pair("assets/pacman_right.png", 0);
        moveRight();
    } else if (key == e_key::P) {
        stop();
    }

    if (_animation) {
        _animation = !_animation;
        _Sprite['P'] = std::make_pair("assets/pacman_full.png", 0);
    } else
        _animation = !_animation;
}

