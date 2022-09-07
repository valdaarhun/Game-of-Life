#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>
#include <vector>

const int CELL_SIZE = 1;
const int WIN_HEIGHT = 800;
const int WIN_WIDTH = 1000;

const int N_ROWS = WIN_HEIGHT / CELL_SIZE;
const int N_COLS = WIN_WIDTH / CELL_SIZE;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

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
                // printf("Alive: %d %d %d\n", i, j, grid[i][j] & 1);
                grid[i][j] = 0;
                drawCell(j, i, 0);
            }
            else if ((grid[i][j] & 1) == DEAD && (grid[i][j] >> 1) == 3){
                // printf("Dead: %d %d %d\n", i, j, grid[i][j] >> 1);
                grid[i][j] = 0;
                grid[i][j] |= 1;
                drawCell(j, i, 255);
            }
        }
    }
}

std::vector< std::pair< int, int > > getTemplate(){
    std::vector< std::pair< int, int > > cells;
    /* (row, col) */

    /* Beacon */
    cells.push_back({40, 40});
    cells.push_back({40, 41});
    cells.push_back({41, 41});
    cells.push_back({41, 40});
    cells.push_back({42, 42});
    cells.push_back({43, 42});
    cells.push_back({43, 43});
    cells.push_back({42, 43});

    /* Blinker */
    // cells.push_back({40, 40});
    // cells.push_back({40, 41});
    // cells.push_back({40, 42});

    /* Toad */
    // cells.push_back({40, 40});
    // cells.push_back({40, 41});
    // cells.push_back({40, 42});
    // cells.push_back({41, 41});
    // cells.push_back({41, 42});
    // cells.push_back({41, 43});

    /* Glider */
    // cells.push_back({40, 40});
    // cells.push_back({40, 41});
    // cells.push_back({40, 42});
    // cells.push_back({39, 42});
    // cells.push_back({38, 41});

    return cells;
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    surface = SDL_GetWindowSurface(window);

    buildWorld();
    // std::vector< std::pair< int, int > > cells = getTemplate();
    // buildFromTemplate(cells);
    getNeighbourCount();
    

    SDL_Event event;
    bool quit = false, running = false;
    int prev = 0, now = 0;
    while(!quit){
        event.type = -1;
        SDL_PollEvent(&event);
        switch (event.type){
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                // nextGeneration();
                // getNeighbourCount();
                running = true;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
                quit = true;
            break;
        default:
            break;
        }
        if (running && (now = SDL_GetTicks()) - prev > 100){
            prev = now;
            nextGeneration();
            getNeighbourCount();
        }
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}