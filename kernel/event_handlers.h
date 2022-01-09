#pragma once

#include "../drivers/keyboard.h"
#include "../drivers/mouse.h"
#include "../drivers/cursor.h"
#include <stdint.h>
#include <stdbool.h>

bool buttons[3];

void key_released(int scancode, char chr);

void key_pressed(int scancode, char chr);

void mouse_start_move(uint8_t x, uint8_t y);

void mouse_move(uint8_t x, uint8_t y);

void mouse_down(uint8_t button);

void mouse_up(uint8_t button);