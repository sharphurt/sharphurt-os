#include <stdbool.h>
#include <stdint.h>

static bool shift_pressed;
static bool caps_lock;
static char key_buffer[256];

char decode_scancode(uint8_t scancode);
void init_keyboard();
