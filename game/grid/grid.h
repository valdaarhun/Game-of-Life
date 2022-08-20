#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>

extern const int PIXELS_X;
extern const int PIXELS_Y;
extern const int PIXELS_PER_CELL;

namespace Game{
    class Grid{
    private:
        int cols = PIXELS_X / PIXELS_PER_CELL;
        int rows = PIXELS_Y / PIXELS_PER_CELL;

        void drawGridLines_XAxis(SDL_Renderer *);
        void drawGridLines_YAxis(SDL_Renderer *);

    public:
        void drawGrid(SDL_Renderer *);
        void colorCell(SDL_Renderer *, int , int);
    };
}

#endif