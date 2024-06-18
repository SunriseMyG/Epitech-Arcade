/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** Core
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <atomic>
#include "libloader/libloader.hpp"
#include "parsing/parsingErrors.hpp"
#include "./DirManager/DirManager.hpp"
#include "../lib/SDL2/SDL.hpp"
#include "../lib/NCurses/Ncurse.hpp"
#include "../games/IGames.hpp"
#include "../lib/IGraphics.hpp"
#include "../keys.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_

    namespace Arcade {
        class Core {
            public:
                Core();
                ~Core();
                IGames *LoadGame(std::string filename);
                IGraphics *LoadGraph(std::string filename);
                void init(std::string graphName);
                void swapGraph();
                void switchGame(IGames *game);
                void switchGraph(IGraphics *graph);
                void switchAll(IGames *game, IGraphics *graph);
                void Loop();
                void saveScore(std::string gameName, int score);
                void setPlayerName(std::string playerName);
                void globalTouch(e_key key);
                void setGlobalTouch(bool stop);
            protected:
            private:
                std::string _playerName;
                IGames *_game;
                IGraphics *_graph;
                bool _run;
                e_key _lastTouch;
                std::vector<std::string> _availableLibs;
                size_t _currentLib;
                bool _stopGlobalTouch;
        };
    }

#endif /* !CORE_HPP_ */
