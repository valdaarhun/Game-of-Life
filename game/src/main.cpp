#include <SDL2/SDL.h>

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 800, SDL_WINDOW_RESIZABLE);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Event event;
    bool quit = false;
    while(!quit){
        SDL_PollEvent(&event);
        switch (event.type){
        case SDL_QUIT:
            quit = true;
            break;
        default:
            break;
        }
    }
}