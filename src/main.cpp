#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>
#include <vector>

const int CELL_SIZE = 10;
const int WIN_HEIGHT = 800;
const int WIN_WIDTH = 1000;

const int N_ROWS = WIN_HEIGHT / CELL_SIZE;
const int N_COLS = WIN_WIDTH / CELL_SIZE;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

bool running = true, animate = false;

typedef enum{
    DEAD,
    ALIVE
}Vitals;

std::vector< std::vector < Uint8 > > grid;

void drawCell(int x, int y, Uint8 color){
    Uint8 *pixels = (Uint8 *)surface -> pixels;
    Uint8 *ptr = pixels + (y * CELL_SIZE * WIN_WIDTH + x * CELL_SIZE) * 4;
    for(int i = 0 ; i < CELL_SIZE ; i++){
        for(int j = 0 ; j < CELL_SIZE ; j++){
            Uint8 *temp =  ptr + (i * WIN_WIDTH + j) * 4;
            *temp = color;
            *(temp + 1) = color;
            *(temp + 2) = color;
            // *(temp + 3) = alpha;
        }
    }
}

void countNeighbours(int x, int y){
    int r[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int c[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int cnt = 0;
    grid[y][x] &= 0x1;
    for (int i = 0 ; i < 8 ; i++){
        int n_x = x + c[i], n_y = y + r[i];
        if (n_x < 0) n_x = N_COLS - 1;
        if (n_x == N_COLS) n_x = 0;
        if (n_y < 0) n_y = N_ROWS - 1;
        if (n_y == N_ROWS) n_y = 0;
        if ((grid[n_y][n_x] & 1) == ALIVE)
            cnt++;
    }
    grid[y][x] |= (cnt << 1);
}

void getNeighbourCount(){
    for(int i = 0 ; i < N_ROWS ; i++){
        for(int j = 0 ; j < N_COLS ; j++)
            countNeighbours(j, i);
    }
}

void buildWorld(){
    std::vector< std::vector< Uint8 > > temp(N_ROWS, std::vector< Uint8 > (N_COLS, 0));
    grid = temp;

    srand(time(nullptr));
    for(int i = 0 ; i < N_COLS * N_ROWS / 8 ; i++){
        int x = rand() % N_COLS, y = rand() % N_ROWS;
        drawCell(x, y, 255);
        grid[y][x] |= ALIVE;
    }
}

void buildFromTemplate(std::vector< std::pair< int, int > > &cells){
    std::vector< std::vector< Uint8 > > temp(N_ROWS, std::vector< Uint8 > (N_COLS, 0));
    grid = temp;
    for(auto cell: cells){
        // printf("%d %d\n", cell.first, cell.second);
        drawCell(cell.second, cell.first, 255);
        grid[cell.first][cell.second] |= ALIVE;
    }
}

void nextGeneration(){
    for(int i = 0 ; i < N_ROWS ; i++){
        for(int j = 0 ; j < N_COLS ; j++){
            if ((grid[i][j] & 1) == ALIVE && ((grid[i][j] >> 1) < 2 || (grid[i][j] >> 1) > 3)){
                grid[i][j] = 0;
                drawCell(j, i, 0);
            }
            else if ((grid[i][j] & 1) == DEAD && (grid[i][j] >> 1) == 3){
                grid[i][j] = 0;
                grid[i][j] |= 1;
                drawCell(j, i, 255);
            }
        }
    }
}

// void poll_event(){
//     SDL_Event event;
//     while(SDL_PollEvent(&event)){
//         switch (event.type){
//         case SDL_QUIT:
//             running = false;
//             break;
//         // case SDL_KEYDOWN:
//         //     if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
//         //         getNeighbourCount();
//         //         animate = true;
//         //     }
//         //     else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
//         //         running = false;
//         //     break;
//         case SDL_MOUSEBUTTONDOWN:
//             // if (animate)
//             //     break;
//             if (event.button.button == SDL_BUTTON_LEFT){
//                 int x, y;
//                 SDL_GetMouseState(&x, &y);
//                 x /= CELL_SIZE;
//                 y /= CELL_SIZE;
//                 drawCell(x, y, 255);
//                 grid[y][x] |= ALIVE;
//             }
//             break;
//         default:
//             break;
//         }
//     }
// }


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    surface = SDL_GetWindowSurface(window);
    std::vector< std::vector< Uint8 > > temp(N_ROWS, std::vector< Uint8 > (N_COLS, 0));
    grid = temp;

    SDL_Event event;
    int prev = 0, now = 0;
    while(running){
        // poll_event();
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                    getNeighbourCount();
                    animate = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                    animate = false;
                else if (event.key.keysym.scancode == SDL_SCANCODE_C)
                    // Clear playground
                    ;
                else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
                    running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // if (animate)
                //     break;
                if (event.button.button == SDL_BUTTON_LEFT){
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    x /= CELL_SIZE;
                    y /= CELL_SIZE;
                    drawCell(x, y, 255);
                    grid[y][x] |= ALIVE;
                }
                break;
            default:
                break;
            }
        }
        if (animate && (now = SDL_GetTicks()) - prev > 100){
            prev = now;
            nextGeneration();
            getNeighbourCount();
        }
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}