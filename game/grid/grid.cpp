#include <SDL2/SDL.h>
#include <utility>
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
    m_cells[y][x] = ALIVE;
}

void Game::Grid::setDead(int x, int y){
    m_cells[y][x] = DEAD;
}

void Game::Grid::createCell(int x, int y){
    SDL_Rect rect;
    setRect(&rect, x, y);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(WHITE >> 16), SET_BYTE(WHITE >> 8), SET_BYTE(WHITE), ALPHA);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_RenderPresent(m_renderer);
    getIndices(&x, &y);
    // printf("%d %d\n", x, y);
    setAlive(x, y);
}

void Game::Grid::killCell(int x, int y){
    SDL_Rect rect;
    setRect(&rect, x, y);
    SDL_SetRenderDrawColor(m_renderer, SET_BYTE(BLACK >> 16), SET_BYTE(BLACK >> 8), SET_BYTE(BLACK), ALPHA);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_RenderPresent(m_renderer);
    getIndices(&x, &y);
    // printf("%d %d\n", x, y);
    setDead(x, y);
}

int Game::Grid::countNeighbours(int y, int x){
    int cnt = 0;
    int r[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int c[] = {0, 1, 1, 1, 0, -1, -1, -1};
    for (int i = 0 ; i < 8 ; i++){
        int n_x = x + c[i], n_y = y + r[i];
        if (n_x < 0 || n_x >= m_cols || n_y < 0 || n_y >= m_rows)
            continue;
        cnt += (m_cells[n_y][n_x] == ALIVE);
    }
    return cnt;
}

void Game::Grid::setToToggle(int r, int c){
    m_coords_toggle.push({r, c});
}

void Game::Grid::render(){
    while(!m_coords_toggle.empty()){
        std::pair< int, int > coords = m_coords_toggle.top();
        printf("(%d, %d)\n", coords.first, coords.second);
        m_coords_toggle.pop();
        int x = coords.first * PIXELS_PER_CELL + 1;
        int y = coords.second * PIXELS_PER_CELL + 1;
        if (m_cells[coords.first][coords.second] == ALIVE)
            killCell(x, y);
        else
            createCell(x, y);
    }
}

void Game::Grid::nextGen(){
    /* Cells outside grid are dead unconditionally */
    for(int i = 0 ; i < m_rows ; i++){
        for(int j = 0 ; j < m_cols ; j++){
            if (m_cells[i][j] == ALIVE){
                int num_neighbours = countNeighbours(i, j);
                // printf("(%d, %d): %d\n", i, j, num_neighbours);
                if (num_neighbours < 2 || num_neighbours > 3)
                    setToToggle(i, j);
            }
            else{
                int num_neighbours = countNeighbours(i, j);
                if (num_neighbours == 3)
                    setToToggle(i, j);
            }
        }
    }
    render();
}