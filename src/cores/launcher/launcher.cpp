/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** launcher
*/

#include "launcher.hpp"

void Launcher::init()
{
    _name = "Launcher";
    _score = 0;
    _life = 0;
    _level = 0;
    _infinite = false;
    _games = {};
    _libs = {};
    _gapHorizontal = 500;
    _gapVertical = 100;

    DirManager dirManager;

    std::vector<std::string> files = dirManager.readDir("./lib/");

    std::vector<std::string> games;
    std::vector<std::string> libs;

    for (const auto &file : files) {
        Arcade::LibLoader libLoader;
        libLoader.loadLib(file);

        if (libLoader.checkFunction("entryPointGame")) {
            games.push_back(file);
        } else if (libLoader.checkFunction("entryPointGraph")) {
            libs.push_back(file);
        }

        libLoader.closeLib();
    }

    if (access("./scores", F_OK) == -1) {
        mkdir("./scores", 0777);
    }

    for (const auto &game : games) {
        std::string gameName = game.substr(game.find_last_of("_") + 1, game.find_last_of(".") - game.find_last_of("_") - 1);
        std::string filename = "./scores/score_" + gameName + ".txt";
        std::vector<std::string> lines;
        if (access(filename.c_str(), F_OK) == -1) {
            std::ofstream file(filename);
            file.close();
        } else {
            std::ifstream file(filename);
            std::string line;
            if (file.is_open()) {
                while (std::getline(file, line)) {
                    lines.push_back(line);
                }
                file.close();
            }
            std::sort(lines.begin(), lines.end(), [](const std::string &a, const std::string &b) {
                std::istringstream issa(a);
                std::istringstream issb(b);
                int scoreA, scoreB;
                issa >> scoreA;
                issb >> scoreB;
                return scoreA > scoreB;
            });
            std::ofstream fileOut(filename);
            for (const auto &line : lines) {
                fileOut << line << "\n";
            }
            fileOut.close();
        }
    }

    _games = games;
    _libs = libs;

    _selectedGameIndex = 0;
    _selectedLibIndex = 0;
    _mode = 0;
    _playerName = "";

    draw();
}

void Launcher::draw()
{
    _Text.clear();

    _Text.push_back(std::make_tuple("Games", std::make_pair(100, _gapVertical), std::make_tuple(255, 255, 255)));

    for (size_t i = 0; i < _games.size(); i++) {
        std::string gameName = _games[i];
        if (gameName.size() >= 2 && gameName.front() == '>' && gameName.back() == '<') {
            gameName = gameName.substr(1, gameName.size() - 2);
        }
        if (i == _selectedGameIndex) {
            gameName = ">" + gameName + "<";
        }
        _Text.push_back(std::make_tuple(gameName, std::make_pair(100, _gapVertical + (i + 1) * 50), std::make_tuple(255, 255, 255)));
    }

    _Text.push_back(std::make_tuple("Libs", std::make_pair(100 + _gapHorizontal, _gapVertical), std::make_tuple(255, 255, 255)));

    for (size_t i = 0; i < _libs.size(); i++) {
        std::string libName = _libs[i];
        if (libName.size() >= 2 && libName.front() == '>' && libName.back() == '<') {
            libName = libName.substr(1, libName.size() - 2);
        }
        if (i == _selectedLibIndex) {
            libName = ">" + libName + "<";
        }
        _Text.push_back(std::make_tuple(libName, std::make_pair(100 + _gapHorizontal, _gapVertical + (i + 1) * 50), std::make_tuple(255, 255, 255)));
    }

    _Text.push_back(std::make_tuple("Scores", std::make_pair(100 + _gapHorizontal * 2, _gapVertical), std::make_tuple(255, 255, 255)));

    std::string gameName = _games[_selectedGameIndex];
    gameName = gameName.substr(gameName.find_last_of("_") + 1, gameName.find_last_of(".") - gameName.find_last_of("_") - 1);
    std::string filename = "./scores/score_" + gameName + ".txt";
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    if (file.is_open()) {
        for(int i = 0; i < 10; ++i) {
            if(std::getline(file, line)) {
                lines.push_back(line);
                _Text.push_back(std::make_tuple(line, std::make_pair(100 + _gapHorizontal * 2, _gapVertical + 50 * (i + 1)), std::make_tuple(255, 255, 255)));
            } else {
                break;
            }
        }
    } else {
        lines.push_back("No score");
        _Text.push_back(std::make_tuple("No score", std::make_pair(100 + _gapHorizontal * 2, _gapVertical + 50), std::make_tuple(255, 255, 255)));
    }

    // std::cout << "---------------DEBUG---------------" << std::endl;
    // printf("Selected game: %s | index: %ld\n", _games[_selectedGameIndex].c_str(), _selectedGameIndex);
    // printf("Selected lib: %s | index: %ld\n", _libs[_selectedLibIndex].c_str(), _selectedLibIndex);

    // for (size_t i = 0; i < _games.size(); i++) {
    //     printf("Game: %s\n", _games[i].c_str());
    // }
    // for (size_t i = 0; i < _libs.size(); i++) {
    //     printf("Lib: %s\n", _libs[i].c_str());
    // }
    // for (size_t i = 0; i < _Text.size(); i++) {
    //     printf("Text: %s\n", std::get<0>(_Text[i]).c_str());
    // }
}

char Launcher::e_keyToChar(e_key touch)
{
    if (touch == e_key::A)
        return 'A';
    if (touch == e_key::B)
        return 'B';
    if (touch == e_key::C)
        return 'C';
    if (touch == e_key::D)
        return 'D';
    if (touch == e_key::E)
        return 'E';
    if (touch == e_key::F)
        return 'F';
    if (touch == e_key::G)
        return 'G';
    if (touch == e_key::H)
        return 'H';
    if (touch == e_key::I)
        return 'I';
    if (touch == e_key::J)
        return 'J';
    if (touch == e_key::K)
        return 'K';
    if (touch == e_key::L)
        return 'L';
    if (touch == e_key::M)
        return 'M';
    if (touch == e_key::N)
        return 'N';
    if (touch == e_key::O)
        return 'O';
    if (touch == e_key::P)
        return 'P';
    if (touch == e_key::Q)
        return 'Q';
    if (touch == e_key::R)
        return 'R';
    if (touch == e_key::S)
        return 'S';
    if (touch == e_key::T)
        return 'T';
    if (touch == e_key::U)
        return 'U';
    if (touch == e_key::V)
        return 'V';
    if (touch == e_key::W)
        return 'W';
    if (touch == e_key::X)
        return 'X';
    if (touch == e_key::Y)
        return 'Y';
    if (touch == e_key::Z)
        return 'Z';
    if (touch == e_key::NUM0)
        return '0';
    if (touch == e_key::NUM1)
        return '1';
    if (touch == e_key::NUM2)
        return '2';
    if (touch == e_key::NUM3)
        return '3';
    if (touch == e_key::NUM4)
        return '4';
    if (touch == e_key::NUM5)
        return '5';
    if (touch == e_key::NUM6)
        return '6';
    if (touch == e_key::NUM7)
        return '7';
    if (touch == e_key::NUM8)
        return '8';
    if (touch == e_key::NUM9)
        return '9';
    if (touch == e_key::SPACE)
        return ' ';
    return 0;
}

void Launcher::menuUsername(e_key touch)
{
    if (touch == e_key::UNKNOWN)
        return;

    if (touch == e_key::ENTER) {
        Launcher::loadSO();
    }

    if (touch == e_key::ESCAPE) {
        _mode = 0;
        _playerName = "";
        _core->setGlobalTouch(false);
        _Text.clear();
        draw();
    }

    if (touch == e_key::SHIFT)
        _maj = !_maj;

    if (touch == e_key::BACKSPACE) {
        if (_playerName.size() > 0) {
            _playerName.pop_back();
        }
    }

    char c = Launcher::e_keyToChar(touch);

    if (c != 0) {
        if (!_maj) {
            c = std::tolower(c);
        }
        _playerName += c;
    }

    _Text.clear();

    _Text.push_back(std::make_tuple("Enter your name: " + _playerName, std::make_pair(100, _gapVertical + 50), std::make_tuple(255, 255, 255)));
}

void Launcher::stop()
{
}

void Launcher::inputs(e_key key)
{
    if (key == e_key::UNKNOWN)
        return;

    if (_mode == 0) {
        if (key == e_key::UP || key == e_key::Z) {
            Launcher::moveUp();
        } else if (key == e_key::DOWN || key == e_key::S) {
            Launcher::moveDown();
        } else if (key == e_key::LEFT || key == e_key::Q) {
            Launcher::moveLeft();
        } else if (key == e_key::RIGHT || key == e_key::D) {
            Launcher::moveRight();
        } else if (key == e_key::ENTER || key == e_key::SPACE) {
            _core->setGlobalTouch(true);
            _maj = true;
            _mode = 1;
        }
    }
    if (_mode == 1) {
        if (key == e_key::ENTER)
            Launcher::loadSO();

        Launcher::menuUsername(key);
    }
}

//move libs games

void Launcher::moveUp()
{
    if (_selectedGameIndex > 0) {
        _selectedGameIndex--;
    } else {
        _selectedGameIndex = _games.size() - 1;
    }
    draw();
}

void Launcher::moveDown()
{
    if (_selectedGameIndex < _games.size() - 1) {
        _selectedGameIndex++;
    } else {
        _selectedGameIndex = 0;
    }
    draw();
}

//move libs graphics

void Launcher::moveLeft()
{
    if (_selectedLibIndex > 0) {
        _selectedLibIndex--;
    } else {
        _selectedLibIndex = _libs.size() - 1;
    }
    draw();
}

void Launcher::moveRight()
{
    if (_selectedLibIndex < _libs.size() - 1) {
        _selectedLibIndex++;
    } else {
        _selectedLibIndex = 0;
    }
    draw();
}

void Launcher::loadSO()
{
    if (_core != nullptr) {
        if (_playerName.empty())
            _playerName = "Player";

        _core->setGlobalTouch(false);
        _core->setPlayerName(_playerName);
        _core->switchAll(_core->LoadGame(_games[_selectedGameIndex]), _core->LoadGraph(_libs[_selectedLibIndex]));
    }
}

const std::string &Launcher::getName() const
{
    return _name;
}

bool Launcher::isInfinite()
{
    return _infinite;
}

void Launcher::setCore(Arcade::Core *core)
{
    _core = core;
}

//SERT A RIEN

const int &Launcher::getScore() const
{
    return _score;
}

const int &Launcher::getLife() const
{
    return _life;
}

const int &Launcher::getLevel() const
{
    return _level;
}

std::vector<std::string> Launcher::getMap()
{
    return _map;
}

const std::map<char, std::pair<std::string, int>> &Launcher::getSprite()
{
    return _Sprite;
}

const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &Launcher::getText()
{
    return _Text;
}