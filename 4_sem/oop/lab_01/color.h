#ifndef COLOR_H
#define COLOR_H

#include <inttypes.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;


color_t color_create(uint8_t r, uint8_t g, uint8_t b);


#endif // COLOR_H
