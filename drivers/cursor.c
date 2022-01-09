#include "cursor.h"

void clear_cursor(uint8_t x, uint8_t y)
{
    invert_at(x, y);
}

void draw_cursor(uint8_t x, uint8_t y)
{
    invert_at(x, y);
}
