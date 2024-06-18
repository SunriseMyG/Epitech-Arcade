/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** SDL
*/

#include "SDL.hpp"


extern "C" IGraphics *entryPointGraph()
{
    return new Arcade::SDL();
}

/**
* @brief Construct a new SDL:: SDL object
* 
* @param window 
*
* Arcade::SDL::SDL()
*
*/
Arcade::SDL::SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() != 0) {
        std::cerr << "TTF initialization failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
* Quit SDL
* 
* @param None
* 
* @return None
* 
* @throw None
*/
Arcade::SDL::~SDL()
{
    TTF_Quit();
    SDL_Quit();
}

/**
* @brief Create a Window object
* 
* @param None
* 
* @return None
* 
* @throw None
*/

#include <filesystem>

void Arcade::SDL::createWindow()
{
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (_window == NULL) {
        std::cerr << "Window creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        std::cerr << "Renderer creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    _font = TTF_OpenFont("assets/arial.ttf", 34);
    if (_font == NULL) {
        std::cerr << "Font creation failed: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(_renderer);
}

/**
* @brief Draw a rectangle on the screen
* 
* @param positionX, positionY, colorR, colorG, colorB
* 
* @return None
* 
* @throw None
*/
void Arcade::SDL::drawRect(int pos_x, int pos_y, int r, int g, int b) const
{
    if (_renderer == NULL) {
        std::cerr << "Renderer creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    _rect = {pos_x, pos_y, 25, 25};
    SDL_SetRenderDrawColor(_renderer, r, g, b, 255);
    SDL_RenderFillRect(_renderer, &_rect);
}

/**
* @brief Destroy the Window object
* 
* @param None
* 
* @return None
* 
* @throw None
*/
void Arcade::SDL::destroyWindow() const
{
    // TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Arcade::SDL::drawSprite(const std::string &text, int pos_x, int pos_y) const
{
    SDL_Surface *surface = IMG_Load(text.c_str());
    if (surface == NULL) {
        std::cerr << "Surface creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == NULL) {
        std::cerr << "Texture creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_Rect rect = {pos_x, pos_y, 25, 25};
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

/**
* @brief Return the input used
* 
* @param None
* 
* @return None
* 
* @throw None
*/
e_key Arcade::SDL::getInput()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            _isRunning = false;
            destroyWindow();
            break;
        }
        else if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_UP: return UP;
                case SDLK_DOWN: return DOWN;
                case SDLK_LEFT: return LEFT;
                case SDLK_RIGHT: return RIGHT;
                case SDLK_SPACE: return SPACE;
                case SDLK_RETURN: return ENTER;
                case SDLK_ESCAPE: return ESCAPE;
                case SDLK_a: return A;
                case SDLK_b: return B;
                case SDLK_c: return C;
                case SDLK_d: return D;
                case SDLK_e: return E;
                case SDLK_f: return F;
                case SDLK_g: return G;
                case SDLK_h: return H;
                case SDLK_i: return I;
                case SDLK_j: return J;
                case SDLK_k: return K;
                case SDLK_l: return L;
                case SDLK_m: return M;
                case SDLK_n: return N;
                case SDLK_o: return O;
                case SDLK_p: return P;
                case SDLK_q: return Q;
                case SDLK_r: return R;
                case SDLK_s: return S;
                case SDLK_t: return T;
                case SDLK_u: return U;
                case SDLK_v: return V;
                case SDLK_w: return W;
                case SDLK_x: return X;
                case SDLK_y: return Y;
                case SDLK_z: return Z;
                case SDLK_0: return NUM0;
                case SDLK_1: return NUM1;
                case SDLK_2: return NUM2;
                case SDLK_3: return NUM3;
                case SDLK_4: return NUM4;
                case SDLK_5: return NUM5;
                case SDLK_6: return NUM6;
                case SDLK_7: return NUM7;
                case SDLK_8: return NUM8;
                case SDLK_9: return NUM9;
                case SDLK_F1: return F1;
                case SDLK_F2: return F2;
                case SDLK_F3: return F3;
                case SDLK_F4: return F4;
                case SDLK_F5: return F5;
                case SDLK_F6: return F6;
                case SDLK_F7: return F7;
                case SDLK_F8: return F8;
                case SDLK_F9: return F9;
                case SDLK_F10: return F10;
                case SDLK_F11: return F11;
                case SDLK_F12: return F12;
                case SDLK_LSHIFT: return SHIFT;
                case SDLK_LALT: return ALT;
                case SDLK_BACKSPACE: return BACKSPACE;
                default: return UNKNOWN;
            }
        }
    }
    return UNKNOWN;
}

void Arcade::SDL::sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> text, std::map<char, std::pair<std::string, int>> sprite)
{
    if (_renderer == NULL) {
        std::cerr << "Renderer creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            _isRunning = false;
            destroyWindow();
            break;
        }
    }
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    if (!map.empty()) {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(_window, &windowWidth, &windowHeight);

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
    _color = {255, 255, 255, 255};
    for (std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>>::size_type i = 0; i < text.size(); i++) {
        std::string currentText = std::get<0>(text[i]);
        if (i < _loadedText.size() && _loadedText[i] == currentText) {
            _surface = TTF_RenderText_Solid(_font, currentText.c_str(), _color);
            if (_surface == NULL) {
                std::cerr << "Surface creation failed." << std::endl;
                exit(EXIT_FAILURE);
            }
            _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
            _rect = {std::get<1>(text[i]).first, std::get<1>(text[i]).second, _surface->w, _surface->h};
            SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
            std::cout << _loadedText[i] << std::endl;
        } else {
            _surface = TTF_RenderText_Solid(_font, currentText.c_str(), _color);
            _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
            _rect = {std::get<1>(text[i]).first, std::get<1>(text[i]).second, _surface->w, _surface->h};
            SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
            if (i < _loadedText.size()) {
                _loadedText[i] = currentText;
            } else {
                _loadedText.push_back(currentText);
            }
        }
    }
    SDL_FreeSurface(_surface);
    SDL_DestroyTexture(_texture);
    SDL_RenderPresent(_renderer);
}
