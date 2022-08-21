#include <SDL2/SDL.h>

#include "../bit_operations/bits.h"
#include "world.h"

extern const int PIXELS_X;
extern const int PIXELS_Y;
extern const int PIXELS_PER_CELL;

static constexpr Uint32 BLACK = 0x000000;
static constexpr Uint32 SLATE = 0x123456;
static constexpr Uint32 WHITE = 0xffffff;
static constexpr Uint8 ALPHA = 0;

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
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(SLATE >> 16), SET_BYTE(SLATE >> 8), SET_BYTE(SLATE), ALPHA);
    drawGridLines_XAxis();
    drawGridLines_YAxis();
    SDL_RenderPresent(m_renderer);

    /* Reset color to white */
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(WHITE >> 16), SET_BYTE(WHITE >> 8), SET_BYTE(WHITE), ALPHA);
}

Game::World::~World(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}