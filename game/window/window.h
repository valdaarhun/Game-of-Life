#pragma once

#include <SDL2/SDL.h>

namespace Game{
    class Window{
    private:
        int m_width;
        int m_height;
        SDL_Window *m_window;

    public:
        SDL_Renderer *renderer;

        Window(int t_width, int t_height)
            : m_width(t_width), m_height(t_height)
        {
            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_RESIZABLE, &m_window, &renderer);
            SDL_SetRenderDrawColor(renderer, 172, 127, 127, 0);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        SDL_Renderer *getRenderer();

        ~Window(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }
    };
}
