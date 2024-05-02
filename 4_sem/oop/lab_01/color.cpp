#include "color.h"

color_t color_create(uint8_t r, uint8_t g, uint8_t b)
{
    color_t c = {
        .r = r,
        .g = g,
        .b = b
    };
    return c;
}
