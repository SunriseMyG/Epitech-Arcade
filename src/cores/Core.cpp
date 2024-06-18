/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"
#include "launcher/launcher.hpp"

Arcade::Core::Core()
{
    _lastTouch = e_key::D;
    _stopGlobalTouch = false;
}

Arcade::Core::~Core()
{
}

IGames *Arcade::Core::LoadGame(std::string filename)
{
    Arcade::LibLoader libLoader;

    libLoader.loadLib(filename);

    libLoader.getLib();

    auto func = libLoader.getFunction("entryPointGame");
    auto _game = reinterpret_cast<IGames *(*)(void)>(func)();

    return _game;
}

IGraphics *Arcade::Core::LoadGraph(std::string filename)
{
    Arcade::LibLoader libLoader;

    libLoader.loadLib(filename);

    libLoader.getLib();

    auto func = libLoader.getFunction("entryPointGraph");
    auto graph = reinterpret_cast<IGraphics *(*)(void)>(func)();

    return graph;
}

void Arcade::Core::init(std::string graphName)
{
    DirManager dirManager;
    std::vector<std::string> files = dirManager.readDir("./lib/");

    for (const auto &file : files) {
        Arcade::LibLoader libLoader;
        libLoader.loadLib(file);

        if (libLoader.checkFunction("entryPointGraph")) {
            _availableLibs.push_back(file);
        }

        libLoader.closeLib();
    }

    for (size_t i = 0; i < _availableLibs.size(); i++) {
        if (_availableLibs[i] == graphName) {
            _currentLib = i;
            break;
        }
    }
}

void Arcade::Core::switchGame(IGames *game)
{
    _run = false;
    _lastTouch = e_key::D;
    if (_game != nullptr) {
        _game = nullptr;
    }
    _game = game;
    if (_game != nullptr) {
        _game->init();
        _run = true;
        Loop();
    } else {
        printf("Game not loaded\n");
    }
}

void Arcade::Core::switchGraph(IGraphics *graph)
{
    _run = false;
    if (_graph != nullptr) {
        _graph->destroyWindow();
        delete _graph;
        _graph = nullptr;
    }
    _graph = graph;
    _graph->createWindow();
}

void Arcade::Core::switchAll(IGames *game, IGraphics *graph)
{
    if (graph != nullptr)
        switchGraph(graph);
    if (game != nullptr)
        switchGame(game);
}

void Arcade::Core::swapGraph()
{
    _run = false;
    _currentLib++;
    if (_currentLib >= _availableLibs.size())
        _currentLib = 0;

    auto graph = LoadGraph(_availableLibs[_currentLib]);
    switchGraph(graph);
    _lastTouch = e_key::D;
    Loop();
}

void Arcade::Core::saveScore(std::string gameName, int score)
{
    if (gameName.empty())
        return;

    if (gameName == "Launcher")
        return;

    std::transform(gameName.begin(), gameName.end(), gameName.begin(), ::tolower);
    std::ofstream file;
    file.open("./scores/score_" + gameName + ".txt", std::ios::app);
    if (file.is_open()) {
        printf("Score saved\n");

        std::string playerName = _playerName;

        if (playerName.empty())
            playerName = "Player";

        file << score << " " << playerName << "\n";
        file.close();
    }
}

void Arcade::Core::Loop()
{
    _run = true;

    bool saved = false;

    auto autoRun = std::chrono::high_resolution_clock::now();

    _graph->sendMap(_game->getMap(), _game->getText(), _game->getSprite());

    while (_run) {
        if (_game == nullptr || _graph == nullptr)
            break;

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - autoRun);

        if (_game->getLife() <= 0 && !saved) {
            saveScore(_game->getName(), _game->getScore());
            saved = true;
        } else if (_game->getLife() > 0) {
            saved = false;
        }

        if (_game->isInfinite()) {
            if (elapsedTime.count() >= 220) {
                _game->inputs(_lastTouch);
                autoRun = currentTime;
                _graph->sendMap(_game->getMap(), _game->getText(), _game->getSprite());
            }
            e_key c = _graph->getInput();
            if (c != e_key::UNKNOWN)
                _lastTouch = c;
            globalTouch(c);
        } else {
            e_key c = _graph->getInput();
            if (c != e_key::UNKNOWN) {
                _game->inputs(c);
                globalTouch(c);
                _graph->sendMap(_game->getMap(), _game->getText(), _game->getSprite());
            }
        }
    }

    _run = false;
}

void Arcade::Core::setGlobalTouch(bool stop)
{
    _stopGlobalTouch = stop;
}

void Arcade::Core::globalTouch(e_key touch)
{
    if (_stopGlobalTouch)
        return;

    if (touch == e_key::E) {
        _run = false;
        saveScore(_game->getName(), _game->getScore());
        _game->stop();
        _graph->destroyWindow();
        exit(0);
    }
    if (touch == e_key::G)
        swapGraph();
    if (touch == e_key::L) {
        Launcher launcher;
        launcher.setCore(this);
        saveScore(_game->getName(), _game->getScore());
        _run = false;
        switchAll(&launcher, LoadGraph(_availableLibs[_currentLib]));
    }
    if (touch == e_key::R) {
        saveScore(_game->getName(), _game->getScore());
        _game->stop();
        _lastTouch = e_key::D;
        _game->init();
    }
}

void Arcade::Core::setPlayerName(std::string playerName)
{
    _playerName = playerName;
}
