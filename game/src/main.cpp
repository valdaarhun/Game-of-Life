#include <SDL2/SDL.h>

#include "world/world.h"
#include "grid/grid.h"

int main(){
    Game::World world(1001, 801);
    world.drawGrid();

    Game::Grid grid;
    grid.setRenderer(world.getRenderer());

    SDL_Event event;
    bool quit = false;

    while(!quit){
        event.type = -1;
        SDL_PollEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (event.button.button == SDL_BUTTON_LEFT)
                grid.createCell(x, y);
            else if (event.button.button == SDL_BUTTON_RIGHT)
                grid.killCell(x, y);
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
                grid.run();
        default:
            break;
        }
    }
}