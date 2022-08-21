#pragma once

#include <SDL2/SDL.h>

namespace Game{
    class World{
    private:
        int m_width;
        int m_height;
        SDL_Renderer *m_renderer;
        SDL_Window *m_window;

        void drawGridLines_XAxis();
        void drawGridLines_YAxis();

    public:
        World(int, int);
        SDL_Renderer *getRenderer();
        void drawGrid();
        ~World();
    };
}
