#pragma once
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include "../kernel/event_handlers.h"
#include <stdint.h>
#include <stdbool.h>


static float mouse_x = SCREEN_WIDTH / 2;
static float mouse_y = SCREEN_HEIGHT / 2;

void init_mouse();

enum MOUSE_BUTTON
{
    LEFT = 1,
    RIGHT = 2,
    MIDDLE = 3
};