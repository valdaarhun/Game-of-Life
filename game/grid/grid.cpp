#include <SDL2/SDL.h>

#include "../utilities/utils.h"
#include "grid.h"

void Game::Grid::getCoords(SDL_Rect *rect, int t_x, int t_y){
    rect -> h = PIXELS_PER_CELL - 1;
    rect -> w = PIXELS_PER_CELL - 1;
    rect -> x = PIXELS_PER_CELL * (t_x / PIXELS_PER_CELL) + 1;
    rect -> y = PIXELS_PER_CELL * (t_y / PIXELS_PER_CELL) + 1;
}

void Game::Grid::setRenderer(SDL_Renderer *renderer){
    m_renderer = renderer;
}

void Game::Grid::createCell(int x, int y){
    SDL_Rect rect;
    getCoords(&rect, x, y);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(WHITE >> 16), SET_BYTE(WHITE >> 8), SET_BYTE(WHITE), ALPHA);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_RenderPresent(m_renderer);
}

void Game::Grid::killCell(int x, int y){
    SDL_Rect rect;
    getCoords(&rect, x, y);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(BLACK >> 16), SET_BYTE(BLACK >> 8), SET_BYTE(BLACK), ALPHA);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_RenderPresent(m_renderer);
}