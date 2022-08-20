#pragma once

#include <SDL2/SDL.h>

static inline Uint8 SET_BYTE(int x){
    return (x) & 0xff;
}