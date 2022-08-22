#include <SDL2/SDL.h>
#include <vector>

#include "../utilities/utils.h"
#include "grid.h"

Game::Grid::Grid(){
    std::vector< std::vector < Vitals > > temp(m_rows, std::vector < Vitals > (m_cols, DEAD));
    m_cells = temp;
}

void Game::Grid::getIndices(int *t_x, int *t_y){
    *t_x /= PIXELS_PER_CELL;
    *t_y /= PIXELS_PER_CELL;
}

/* Is it possible to merge getCoords with setRect? */
void Game::Grid::getCoords(int *t_x, int *t_y){
    *t_x = PIXELS_PER_CELL * (*t_x / PIXELS_PER_CELL) + 1;
    *t_y = PIXELS_PER_CELL * (*t_y / PIXELS_PER_CELL) + 1;
}

void Game::Grid::setRect(SDL_Rect *rect, int t_x, int t_y){
    rect -> h = PIXELS_PER_CELL - 2;
    rect -> w = PIXELS_PER_CELL - 2;
    getCoords(&t_x, &t_y);
    rect -> x = t_x;
    rect -> y = t_y;
}

void Game::Grid::setRenderer(SDL_Renderer *renderer){
    m_renderer = renderer;
}

void Game::Grid::setAlive(int x, int y){
    getIndices(&x, &y);
    printf("%d %d\n", x, y);
    m_cells[y][x] = ALIVE;
}

void Game::Grid::setDead(int x, int y){
    getIndices(&x, &y);
    printf("%d %d\n", x, y);
    m_cells[y][x] = DEAD;
}

void Game::Grid::createCell(int x, int y){
    SDL_Rect rect;
    setRect(&rect, x, y);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(WHITE >> 16), SET_BYTE(WHITE >> 8), SET_BYTE(WHITE), ALPHA);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_RenderPresent(m_renderer);
    setAlive(x, y);
}

void Game::Grid::killCell(int x, int y){
    SDL_Rect rect;
    setRect(&rect, x, y);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(BLACK >> 16), SET_BYTE(BLACK >> 8), SET_BYTE(BLACK), ALPHA);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_RenderPresent(m_renderer);
    setDead(x, y);
}

void Game::Grid::run(){

}