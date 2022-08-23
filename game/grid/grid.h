#pragma once

#include <SDL2/SDL.h>
#include <stack>
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
        std::stack< std::pair < int, int > > m_coords_toggle;

        void getIndices(int *, int *);
        void getCoords(int *, int *);
        void setRect(SDL_Rect *, int, int);
        void setAlive(int, int);
        void setDead(int, int);
        int countNeighbours(int, int);
        void setToToggle(int, int);
        void render();

    public:
        Grid();
        void setRenderer(SDL_Renderer *);
        void createCell(int, int);
        void killCell(int, int);
        void nextGen();
    };
}