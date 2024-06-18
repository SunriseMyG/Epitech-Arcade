/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** SFML
*/

#include "SFML.hpp"

extern "C" IGraphics *entryPointGraph()
{
    return new Arcade::SFML();
}

void Arcade::SFML::createWindow()
{
    _window.create(sf::VideoMode::getDesktopMode(), "Arcade", sf::Style::Titlebar | sf::Style::Close);
    _window.setFramerateLimit(60);
    _view.reset(sf::FloatRect(0, 0, _window.getSize().x, _window.getSize().y));
    _window.clear();
    _font.loadFromFile("assets/arial.ttf");
    _window.display();
}

void Arcade::SFML::destroyWindow() const
{
    _window.close();
}

void Arcade::SFML::drawRect(int pos_x, int pos_y, int r, int g, int b) const
{
    _rect.setSize(sf::Vector2f(25, 25));
    _rect.setFillColor(sf::Color(r, g, b));
    _rect.setPosition(pos_x, pos_y);
    _window.draw(_rect);
}

void Arcade::SFML::drawSprite(const std::string &text, int pos_x, int pos_y) const
{
    if (!_texture.loadFromFile(text)) {
        return;
    }

    _sprite.setTexture(_texture);
    _sprite.setPosition(pos_x, pos_y);

    sf::Vector2u textureSize = _texture.getSize();
    _sprite.setScale(
        25.0f / textureSize.x,
        25.0f / textureSize.y
    );

    _window.draw(_sprite);
}

e_key Arcade::SFML::getInput()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::Resized) {
            _view.setCenter(_window.getSize().x / 2, _window.getSize().y / 2);
            _window.setView(_view);
        }
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Up: return UP;
                case sf::Keyboard::Down: return DOWN;
                case sf::Keyboard::Left: return LEFT;
                case sf::Keyboard::Right: return RIGHT;
                case sf::Keyboard::Space: return SPACE;
                case sf::Keyboard::Return: return ENTER;
                case sf::Keyboard::Escape: return ESCAPE;
                case sf::Keyboard::A: return A;
                case sf::Keyboard::B: return B; 
                case sf::Keyboard::C: return C;
                case sf::Keyboard::D: return D;
                case sf::Keyboard::E: return E;
                case sf::Keyboard::F: return F;
                case sf::Keyboard::G: return G;
                case sf::Keyboard::H: return H;
                case sf::Keyboard::I: return I;
                case sf::Keyboard::J: return J;
                case sf::Keyboard::K: return K;
                case sf::Keyboard::L: return L;
                case sf::Keyboard::M: return M;
                case sf::Keyboard::N: return N;
                case sf::Keyboard::O: return O;
                case sf::Keyboard::P: return P;
                case sf::Keyboard::Q: return Q;
                case sf::Keyboard::R: return R;
                case sf::Keyboard::S: return S;
                case sf::Keyboard::T: return T;
                case sf::Keyboard::U: return U;
                case sf::Keyboard::V: return V;
                case sf::Keyboard::W: return W;
                case sf::Keyboard::X: return X;
                case sf::Keyboard::Y: return Y;
                case sf::Keyboard::Z: return Z;
                case sf::Keyboard::Num0: return NUM0;
                case sf::Keyboard::Num1: return NUM1;
                case sf::Keyboard::Num2: return NUM2;
                case sf::Keyboard::Num3: return NUM3;
                case sf::Keyboard::Num4: return NUM4;
                case sf::Keyboard::Num5: return NUM5;
                case sf::Keyboard::Num6: return NUM6;
                case sf::Keyboard::Num7: return NUM7;
                case sf::Keyboard::Num8: return NUM8;
                case sf::Keyboard::Num9: return NUM9;
                case sf::Keyboard::F12: return F12;
                case sf::Keyboard::LShift: return SHIFT;
                case sf::Keyboard::LControl: return CTRL;
                case sf::Keyboard::LAlt: return ALT;
                case sf::Keyboard::Tab: return TAB;
                case sf::Keyboard::BackSpace: return BACKSPACE;
                case sf::Keyboard::Insert: return INSERT;
                case sf::Keyboard::Home: return HOME;
                case sf::Keyboard::PageUp: return PAGEUP;
                case sf::Keyboard::Delete: return DELETE;
                case sf::Keyboard::End: return END;
                case sf::Keyboard::PageDown: return PAGEDOWN;
                default: return UNKNOWN;
            }
        }
    }
    return UNKNOWN;
}

void Arcade::SFML::sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> text, std::map<char, std::pair<std::string, int>> sprite)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::Resized) {
            _view.setCenter(_window.getSize().x / 2, _window.getSize().y / 2);
            _window.setView(_view);
        }
    }

    _window.clear();

    if (!map.empty()) {
        int windowWidth = _window.getSize().x;
        int windowHeight = _window.getSize().y;

        int offsetX = (windowWidth - map.size() * 25) / 2;
        int offsetY = (windowHeight - map[0].size() * 25) / 2;

        for (std::map<char, std::pair<std::string, int>>::size_type i = 0; i < map.size(); i++) {
            for (std::map<char, std::pair<std::string, int>>::size_type j = 0; j < map[i].size(); j++) {
                if (sprite.find(map[i][j]) != sprite.end()) {
                    drawSprite(sprite[map[i][j]].first, j * 25 + offsetX, i * 25 + offsetY);
                } else {
                    drawRect(j * 25 + offsetX, i * 25 + offsetY, 0, 0, 0);
                }
            }
        }
    }

    for (std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>>::size_type i = 0; i < text.size(); i++) {
        std::string currentText = std::get<0>(text[i]);

        if (i < _loadedText.size() && _loadedText[i] == currentText) {
            _window.draw(_text[i]);
        } else {
            sf::Text tmp;
            int x = std::get<1>(text[i]).first;
            int y = std::get<1>(text[i]).second;
            tmp.setFont(_font);
            tmp.setString(currentText);
            tmp.setCharacterSize(24);
            tmp.setFillColor(sf::Color(std::get<0>(std::get<2>(text[i])), std::get<1>(std::get<2>(text[i])), std::get<2>(std::get<2>(text[i]))));
            tmp.setPosition(x, y);

            if (i < _text.size()) {
                _text[i] = tmp;
            } else {
                _text.push_back(tmp);
            }

            if (i < _loadedText.size()) {
                _loadedText[i] = currentText;
            } else {
                _loadedText.push_back(currentText);
            }

            _window.draw(_text[i]);
        }
    }
    _window.display();
}
