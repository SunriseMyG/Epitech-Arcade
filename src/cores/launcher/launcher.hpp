/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** launcher
*/

#ifndef LAUNCHER_HPP_
#define LAUNCHER_HPP_

    #include "../../games/IGames.hpp"
    #include "../DirManager/DirManager.hpp"
    #include "../libloader/libloader.hpp"
    #include "../../lib/IGraphics.hpp"
    #include <iostream>
    #include <vector>
    #include <string>
    #include <list>
    #include <ctime>
    #include <cstdlib>
    #include "../Core.hpp"
    #include <sys/stat.h>
    #include <algorithm>
    #include <sstream>

    class Launcher : public IGames {
        public:
            Launcher() = default;
            ~Launcher() = default;
            void init();
            void stop();

            void inputs(e_key key);

            const std::string &getName() const;
            const int &getScore() const;
            const int &getLife() const;
            const int &getLevel() const;
            //const int &getTimer() const;

            bool isInfinite();

            std::vector<std::string> getMap();
            const std::map<char, std::pair<std::string, int>> &getSprite();
            const std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> &getText();
            void loadSO();

            //move libs games
            void moveUp();
            void moveDown();
            //move libs graphics
            void moveLeft();
            void moveRight();
            void select();
            void draw();
            void debugPrintTexts();
            void setCore(Arcade::Core *core);
            void menuUsername(e_key key);
            char e_keyToChar(e_key key);
        protected:
        private:
            //IGame variables
            std::string _name;
            int _score;
            int _life;
            int _level;
            std::vector<std::string> _map;
            bool _infinite;
            std::vector<std::string> _games;
            std::vector<std::string> _libs;
            std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> _Text;
            size_t _selectedGameIndex;
            size_t _selectedLibIndex;
            int _gapHorizontal;
            int _gapVertical;
            Arcade::Core *_core;
            std::string _playerName;
            int _mode;
            bool _maj;
    };

#endif /* !LAUNCHER_HPP_ */
