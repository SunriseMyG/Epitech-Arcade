/*
** EPITECH PROJECT, 2024
** B-OOP-400-NCE-4-1-arcade-steven.deffontaine
** File description:
** Ncurse
*/

#include "Ncurse.hpp"

extern "C" IGraphics *entryPointGraph()
{
    return new Arcade::Ncurse();
}

void Arcade::Ncurse::createWindow()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void Arcade::Ncurse::destroyWindow() const
{
    endwin();
}

void Arcade::Ncurse::drawRect(int pos_x, int pos_y, int r, int g, int b) const
{
    (void)r;
    (void)g;
    (void)b;
    attron(COLOR_PAIR(1));
    mvprintw(pos_y, pos_x, " ");
    attroff(COLOR_PAIR(1));
}

e_key Arcade::Ncurse::getInput()
{
    int ch = getch();

    switch (ch) {
        case KEY_UP: return UP;
        case KEY_DOWN: return DOWN;
        case KEY_LEFT: return LEFT;
        case KEY_RIGHT: return RIGHT;
        case 27: return ESCAPE;
        case 32: return SPACE;
        case 10: return ENTER;
        case 97: return A;
        case 98: return B;
        case 99: return C;
        case 100: return D;
        case 101: return E;
        case 102: return F;
        case 103: return G;
        case 104: return H;
        case 105: return I;
        case 106: return J;
        case 107: return K;
        case 108: return L;
        case 109: return M;
        case 110: return N;
        case 111: return O;
        case 112: return P;
        case 113: return Q;
        case 114: return R;
        case 115: return S;
        case 116: return T;
        case 117: return U;
        case 118: return V;
        case 119: return W;
        case 120: return X;
        case 121: return Y;
        case 122: return Z;
        case 48: return NUM0;
        case 49: return NUM1;
        case 50: return NUM2;
        case 51: return NUM3;
        case 52: return NUM4;
        case 53: return NUM5;
        case 54: return NUM6;
        case 55: return NUM7;
        case 56: return NUM8;
        case 57: return NUM9;
        case KEY_SLEFT: return SHIFT;
        default: return UNKNOWN;
    }

    return UNKNOWN;
}

void Arcade::Ncurse::drawSprite(const std::string &text, int pos_x, int pos_y) const
{
    mvprintw(pos_y, pos_x, "%s", text.c_str());
}

void Arcade::Ncurse::sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> text, std::map<char, std::pair<std::string, int>> sprite)
{
    clear();

    (void)sprite;
    
    if (!map.empty()) {
      int max_y = 0, max_x = 0;
      getmaxyx(stdscr, max_y, max_x);

      int start_y = (max_y - map.size()) / 2;
      int start_x = (max_x - map[0].size()) / 2;

      for (size_t i = 0; i < map.size(); i++) {
          mvprintw(start_y + i, start_x, map[i].c_str());
      }
      for (const auto &elem : _loadedText) {
          const auto &[text, pos] = elem;
          mvprintw(pos.second, pos.first, text.c_str());
      }
    }
    for (auto &elem : text) {
        std::string str = std::get<0>(elem);
        int pos_x = std::get<1>(elem).first / 10;
        int pos_y = std::get<1>(elem).second / 50;

        if (_loadedText.find(str) != _loadedText.end() && _loadedText[str] != std::make_pair(pos_x, pos_y)) {
            mvprintw(_loadedText[str].second, _loadedText[str].first, std::string(str.length(), ' ').c_str());
        }

        _loadedText[str] = std::make_pair(pos_x, pos_y);
        mvprintw(pos_y, pos_x, str.c_str());
    }
    refresh();
}