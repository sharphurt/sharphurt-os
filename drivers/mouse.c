#include "mouse.h"

uint8_t mouse_cycle = 0; // unsigned char
int8_t mouse_byte[3];    // signed char

static uint8_t buttons_byte;

bool first_run = true;

static void mouse_callback(registers_t *regs)
{
    switch (mouse_cycle)
    {
    case 0:
        mouse_byte[0] = port_byte_in(0x60);
        process_mouse_buttons();
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
    if (mouse_byte[1] == 0 && mouse_byte[2] == 0)
        return;

    if (!first_run)
        mouse_start_move(mouse_x, mouse_y);

    first_run = false;

    on_mouse_move();
}

void process_mouse_buttons()
{
    uint8_t i;
    for (i = 0; i < 3; i++)
    {
        if ((mouse_byte[0] & (0x1 << i)) != (buttons_byte & (0x1 << i)))
        {
            if (buttons_byte & (0x1 << i))
                mouse_up(i + 1);
            else
                mouse_down(i + 1);
        }
    }

    buttons_byte = mouse_byte[0];
}

void on_mouse_move()
{
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

    mouse_move(mouse_x, mouse_y);
}

void init_mouse()
{
    uint8_t _status;

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

inline void mouse_wait(uint8_t a_type)
{
    uint32_t _time_out = 100000;
    if (a_type == 0)
    {
        while (_time_out--)
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
        while (_time_out--)
        {
            if ((port_byte_in(0x64) & 2) == 0)
            {
                return;
            }
        }
        return;
    }
}

inline void mouse_write(uint8_t a_write)
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