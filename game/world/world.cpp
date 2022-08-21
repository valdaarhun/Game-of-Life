#include <SDL2/SDL.h>

#include "../utilities/utils.h"
#include "world.h"

Game::World::World(int t_width, int t_height){
    m_width = t_width;
    m_height = t_height;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(BLACK >> 16), SET_BYTE(BLACK >> 8), SET_BYTE(BLACK), ALPHA);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

SDL_Renderer *Game::World::getRenderer(){
    return m_renderer;
}

void Game::World::drawGridLines_XAxis(){
    for(int j = 0 ; j <= PIXELS_Y ; j += PIXELS_PER_CELL){
        SDL_RenderDrawLine(m_renderer, 0, j, PIXELS_X, j);
    }
}

void Game::World::drawGridLines_YAxis(){
    for(int i = 0 ; i <= PIXELS_X ; i += PIXELS_PER_CELL){
        SDL_RenderDrawLine(m_renderer, i, 0, i, PIXELS_Y);
    }
}

void Game::World::drawGrid(){
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(BLUE >> 16), SET_BYTE(BLUE >> 8), SET_BYTE(BLUE), ALPHA);
    drawGridLines_XAxis();
    drawGridLines_YAxis();
    SDL_RenderPresent(m_renderer);
}

Game::World::~World(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}