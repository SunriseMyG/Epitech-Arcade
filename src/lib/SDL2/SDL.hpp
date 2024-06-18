/*
** EPITECH PROJECT, 2024
** opp [WSL : Ubuntu]
** File description:
** SDL
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../IGraphics.hpp"
#include <tuple>

    #ifndef SDL_HPP_
        #define SDL_HPP_

        namespace Arcade {
            class SDL : public IGraphics {
                public:
                    SDL();
                    ~SDL();

                    e_key getInput();
                    void createWindow();
                    void destroyWindow() const;
                    void drawRect(int pos_x, int pos_y, int r, int g, int b) const;
                    void drawSprite(const std::string &text, int pos_x, int pos_y) const;
                    void sendMap(const std::vector<std::string> &map, std::vector<std::tuple<std::string, std::pair<int, int>, std::tuple<int, int, int>>> text, std::map<char, std::pair<std::string, int>> sprite);

                protected:
                private:
                    mutable SDL_Window *_window;
                    mutable SDL_Rect _rect;
                    mutable SDL_Event _event;
                    mutable SDL_Renderer *_renderer;
                    mutable TTF_Font *_font;
                    mutable SDL_Surface *_surface;
                    mutable SDL_Texture *_texture;
                    mutable SDL_Color _color;
                    mutable SDL_Rect _rectText;
                    mutable bool _isRunning = true;
                    std::vector<std::string> _loadedText;
            };
        }

#endif /* !SDL_HPP_ */
