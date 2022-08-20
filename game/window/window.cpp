#include <SDL2/SDL.h>

#include "window.h"

SDL_Renderer *Game::Window::getRenderer(){
    return renderer;
}