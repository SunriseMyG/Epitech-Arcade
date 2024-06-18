/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** SFML
*/

#include "../IGraphics.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#ifndef SFML_HPP_
    #define SFML_HPP_

    namespace Arcade {
        class SFML : public IGraphics {
            public:
                SFML() = default;
                ~SFML() = default;
                e_key getInput();
                void createWindow();
                void destroyWindow() const;
                void drawRect(int pos_x, int pos_y, int r, int g, int b) const;
                void drawSprite(const std::string &text, int pos_x, int pos_y) const;
                void sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> text, std::map<char, std::pair<std::string, int>> sprite);
            private:
                mutable sf::RenderWindow _window;
                mutable sf::Font _font;
                mutable std::vector<sf::Text> _text;
                mutable sf::RectangleShape _rect;
                mutable sf::Texture _texture;
                mutable sf::Sprite _sprite;
                mutable sf::Event _event;
                mutable sf::View _view;
                std::vector<std::string> _loadedText;
        };
    }

#endif /* !SFML_HPP_ */
