#include <SDL2/SDL.h>

#define COLS 10
#define ROWS 8
#define PIXELS_PER_CELL 100

class Window{
private:
    int height;
    int width;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Window(int _width, int _height)
        : width(_width), height(_height)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 172, 127, 127, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_Renderer *getRenderer(){
        return renderer;
    }

    ~Window(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

class Grid{
private:
    int cols;
    int rows;

    void drawGridLines_XAxis(SDL_Renderer *renderer){
        for(int j = 0 ; j < 801 ; j += 10){
            SDL_RenderDrawLine(renderer, 0, j, 1000, j);
        }
    }

    void drawGridLines_YAxis(SDL_Renderer *renderer){
        for(int i = 0 ; i < 1001 ; i += 10){
            SDL_RenderDrawLine(renderer, i, 0, i, 799);
        }
    }

public:
    Grid()
        : cols(COLS), rows(ROWS){}
    
    void drawGrid(SDL_Renderer *renderer){
        drawGridLines_XAxis(renderer);
        drawGridLines_YAxis(renderer);
        SDL_RenderPresent(renderer);
    }
};

int main(){
    Window win(1001, 801);
    Grid grid;
    grid.drawGrid(win.getRenderer());

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