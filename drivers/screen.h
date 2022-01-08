#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/ports.h"
#include "../libc/mem.h"
#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define BLUE_ON_WHITE 0xf1
#define WHITE_ON_BLUE 0x1f

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen(char colorcode);
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void kprint_at_attr(char *message, int col, int row, char attr);
void kprint_attr(char *message, char attr);
void kprint_backspace();

void invert_at(uint8_t col, uint8_t row);

#endif
