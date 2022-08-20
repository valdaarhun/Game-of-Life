#include <SDL2/SDL.h>

#include "window/window.h"
#include "grid/grid.h"

constexpr int PIXELS_X = 1000;
constexpr int PIXELS_Y = 800;
constexpr int PIXELS_PER_CELL = 10;

class Cell{
private:
    int cx;
    int cy;
};

int main(){
    Game::Window win(1001, 801);
    Game::Grid grid;
    SDL_Renderer *renderer = win.getRenderer();
    grid.drawGrid(renderer);

    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    while(event.type != SDL_QUIT){
        if(event.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            printf("(%d, %d)\n", x, y);
            printf("(%d, %d)\n\n", 10 * (x / 10), 10 * (y / 10));
            event.type = -1;
            grid.colorCell(renderer, x, y);
        }
        SDL_PollEvent(&event);
    }
}