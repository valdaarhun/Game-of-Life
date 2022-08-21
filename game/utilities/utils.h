#pragma once

#include <stdint.h>

constexpr int PIXELS_X = 1000;
constexpr int PIXELS_Y = 800;
constexpr int PIXELS_PER_CELL = 10;

constexpr uint32_t WHITE = 0xffffff;
constexpr uint32_t BLACK = 0x000000;
constexpr uint32_t BLUE = 0x123456;
constexpr uint8_t ALPHA = 255;

static inline uint8_t SET_BYTE(int x){
    return (x) & 0xff;
}