#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "../utilities/utils.h"

namespace Game{
    typedef enum{
        ALIVE,
        DEAD,
    }Vitals;

    class Grid{
    private:
        const int m_cols = PIXELS_X / PIXELS_PER_CELL;
        const int m_rows = PIXELS_Y / PIXELS_PER_CELL;
        SDL_Renderer *m_renderer;
        std::vector< std::vector< Vitals > > m_cells;

        void getIndices(int *, int *);
        void getCoords(int *, int *);
        void setRect(SDL_Rect *, int, int);
        void setAlive(int, int);
        void setDead(int, int);

    public:
        Grid();
        void setRenderer(SDL_Renderer *);
        void createCell(int, int);
        void killCell(int, int);
        void run();
    };
}