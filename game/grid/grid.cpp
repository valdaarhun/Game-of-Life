#include <SDL2/SDL.h>

#include "grid.h"

extern const int PIXELS_X;
extern const int PIXELS_Y;
extern const int PIXELS_PER_CELL;

void Game::Grid::drawGridLines_XAxis(SDL_Renderer *renderer){
    for(int j = 0 ; j <= PIXELS_Y ; j += PIXELS_PER_CELL){
        SDL_RenderDrawLine(renderer, 0, j, PIXELS_X, j);
    }
}

void Game::Grid::drawGridLines_YAxis(SDL_Renderer *renderer){
    for(int i = 0 ; i <= PIXELS_X ; i += PIXELS_PER_CELL){
        SDL_RenderDrawLine(renderer, i, 0, i, PIXELS_Y);
    }
}

void Game::Grid::drawGrid(SDL_Renderer *renderer){
    drawGridLines_XAxis(renderer);
    drawGridLines_YAxis(renderer);
    SDL_RenderPresent(renderer);
}

void Game::Grid::colorCell(int x, int y){
}
