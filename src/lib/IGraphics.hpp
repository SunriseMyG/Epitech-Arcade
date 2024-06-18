/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** IGraphics
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

#ifndef IGRAPHICS_HPP_
    #define IGRAPHICS_HPP_

    #include "../keys.hpp"

    class IGraphics {
        public:

            IGraphics() = default;
            virtual ~IGraphics() = default;

            virtual e_key getInput() = 0;
            virtual void createWindow() = 0;
            virtual void destroyWindow() const = 0;
            virtual void drawSprite(const std::string &text, int pos_x, int pos_y) const = 0;
            // virtual void drawRect(int pos_x, int pos_y, int r, int g, int b) const = 0;
            virtual void sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string,
                std::pair<int, int>, std::tuple<int, int, int>>> _Text, std::map<char, std::pair<std::string, int>> _Sprite) = 0;

        private:
    };

#endif /* !IGRAPHICS_HPP_ */
