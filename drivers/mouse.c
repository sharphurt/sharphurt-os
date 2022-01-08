#include "mouse.h"
#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include <stdint.h>
#include <stdbool.h>

uint8_t mouse_cycle = 0; // unsigned char
int8_t mouse_byte[3];    // signed char

static bool cursor_visible = true;
static float sensitivity = 0.1;

static float mouse_x = SCREEN_WIDTH / 2;
static float mouse_y = SCREEN_HEIGHT / 2;

bool first_run = true;

static void mouse_callback(registers_t *regs)
{
    switch (mouse_cycle)
    {
    case 0:
        mouse_byte[0] = port_byte_in(0x60);
        mouse_cycle++;
        break;
    case 1:
        mouse_byte[1] = port_byte_in(0x60);
        mouse_cycle++;
        break;
    case 2:
        mouse_byte[2] = port_byte_in(0x60);
        process_mouse_packet();
        mouse_cycle = 0;
        break;
    }
}

void process_mouse_packet()
{
    if (cursor_visible && !first_run)
        clear_cursor();
    
    first_run = false;
    
    if (mouse_byte[1] != 0 || mouse_byte[2] != 0)
        on_mouse_move();

    if (cursor_visible)
        draw_cursor();

    print_mouse_coords();
}

void on_mouse_move() {
    mouse_x += mouse_byte[1] * sensitivity;
    mouse_y -= mouse_byte[2] * sensitivity;

    if (mouse_x >= SCREEN_WIDTH)
        mouse_x = SCREEN_WIDTH - 1;
    if (mouse_x < 0)
        mouse_x = 0;

    if (mouse_y >= SCREEN_HEIGHT)
        mouse_y = SCREEN_HEIGHT - 1;
    if (mouse_y < 0)
        mouse_y = 0;
}

void clear_cursor()
{
    invert_at((int)mouse_x, (int)mouse_y);
}

void draw_cursor()
{
    invert_at((int)mouse_x, (int)mouse_y);
}

void print_mouse_coords()
{
    char mousex_str[16] = "";
    int_to_ascii(mouse_x, mousex_str);

    char mousey_str[16] = "";
    int_to_ascii(mouse_y, mousey_str);

    char mouse_str[16] = "";
    strcat(mouse_str, mousex_str);
    strcat(mouse_str, " ");
    strcat(mouse_str, mousey_str);

    kprint_at_attr("         ", 0, 0, BLUE_ON_WHITE);
    kprint_at_attr(mouse_str, 0, 0, BLUE_ON_WHITE);
}

void init_mouse()
{
    unsigned char _status; // unsigned char

    // Enable the auxiliary mouse device
    mouse_wait(1);
    port_byte_out(0x64, 0xA8);

    // Enable the interrupts
    mouse_wait(1);
    port_byte_out(0x64, 0x20);
    mouse_wait(0);
    _status = (port_word_in(0x60) | 2);
    mouse_wait(1);
    port_byte_out(0x64, 0x60);
    mouse_wait(1);
    port_byte_out(0x60, _status);

    // Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read(); // Acknowledge

    // Enable the mouse
    mouse_write(0xF4);
    mouse_read(); // Acknowledge

    // Setup the mouse handler
    register_interrupt_handler(IRQ12, mouse_callback);
}

inline void mouse_wait(unsigned char a_type) // unsigned char
{
    uint32_t _time_out = 100000; // unsigned int
    if (a_type == 0)
    {
        while (_time_out--) // Data
        {
            if ((port_byte_in(0x64) & 1) == 1)
            {
                return;
            }
        }
        return;
    }
    else
    {
        while (_time_out--) // Signal
        {
            if ((port_byte_in(0x64) & 2) == 0)
            {
                return;
            }
        }
        return;
    }
}

inline void mouse_write(unsigned char a_write) // unsigned char
{
    // Wait to be able to send a command
    mouse_wait(1);
    // Tell the mouse we are sending a command
    port_byte_out(0x64, 0xD4);
    // Wait for the final part
    mouse_wait(1);
    // Finally write
    port_byte_out(0x60, a_write);
}

void mouse_read()
{
    // Get's response from mouse
    mouse_wait(0);
    port_byte_in(0x60);
}