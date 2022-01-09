#pragma once
#include "mouse.h"
#include "screen.h"
#include <stdbool.h>

static bool cursor_visible = true;
static float sensitivity = 0.1;

void clear_cursor(uint8_t x, uint8_t y);
void draw_cursor(uint8_t x, uint8_t y);
