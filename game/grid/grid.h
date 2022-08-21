#pragma once

#include <SDL2/SDL.h>

#include "../utilities/utils.h"

namespace Game{
    typedef enum{
        ALIVE,
        DEAD,
    }Vitals;

    class Grid{
    private:
        int m_cols = PIXELS_X / PIXELS_PER_CELL;
        int m_rows = PIXELS_Y / PIXELS_PER_CELL;
        SDL_Renderer *m_renderer;
        // Vitals cells[][];

        void getCoords(SDL_Rect *, int, int);

    public:
        void setRenderer(SDL_Renderer *);
        void createCell(int, int);
        void killCell(int, int);
    };
}