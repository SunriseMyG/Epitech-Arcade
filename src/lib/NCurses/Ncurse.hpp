/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** Ncurse
*/

#include "ncurses.h"
#include "../IGraphics.hpp"
#include <unistd.h>
#include <iostream>
#include <set>
#include <tuple>
#include <map>

#ifndef NCURSE_HPP_
    #define NCURSE_HPP_
    namespace Arcade  {
        class Ncurse : public IGraphics {
            public:
                Ncurse() = default;
                ~Ncurse() = default;

                e_key getInput();
                void createWindow();
                void destroyWindow() const;
                void drawRect(int pos_x, int pos_y, int r, int g, int b) const;
                void drawSprite(const std::string &text, int pos_x, int pos_y) const;
                void sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> text, std::map<char, std::pair<std::string, int>> sprite);

            protected:
            private:
                std::map<std::string, std::pair<int, int>> _loadedText;

        };
    }

#endif /* !NCURSE_HPP_ */
