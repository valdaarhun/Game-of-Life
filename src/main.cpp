#include <SDL2/SDL.h>

class Window{
    private:
    int height;
    int width;
    SDL_Window *window;
    SDL_Renderer *renderer;

    public:
    Window(int _width, int _height) :
        width(_width), height(_height)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    void renderPoint(int x, int y){
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderPresent(renderer);
    }

    void grabMouse(){
        SDL_SetWindowGrab(window, SDL_TRUE);
    }

    ~Window(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(){
    Window win(1000, 500);
    win.renderPoint(400, 200);
    
    SDL_Event event;

    while(event.type != SDL_QUIT){
        if(event.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            printf("(%d, %d)\n", x, y);
            event.type = -1;
        }
        SDL_PollEvent(&event);
    }
}