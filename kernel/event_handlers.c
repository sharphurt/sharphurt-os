#include "event_handlers.h"

void key_released(int scancode, char chr)
{

}

void key_pressed(int scancode, char chr)
{
    // if (strcmp(input, "END") == 0)
    // {
    //     kprint("Stopping the CPU. Bye!\n");
    //     asm volatile("hlt");
    // }
    // else if (strcmp(input, "PAGE") == 0)
    // {
    //     uint32_t phys_addr;
    //     uint32_t page = kmalloc(1000, 1, &phys_addr);
    //     char page_str[16] = "";
    //     hex_to_ascii(page, page_str);
    //     char phys_str[16] = "";
    //     hex_to_ascii(phys_addr, phys_str);
    //     kprint("Page: ");
    //     kprint(page_str);
    //     kprint(", physical address: ");
    //     kprint(phys_str);
    //     kprint("\n");
    // }
    // kprint("You said: ");
    // kprint(input);

    // char str = "      ";
    // int_to_ascii(scancode, str);

    char str[3] = {chr, '\0'};
    // kprint("\n> ");
    kprint(str);
}

void mouse_start_move(uint8_t x, uint8_t y)
{
    if (cursor_visible)
        clear_cursor(x, y);
}

void mouse_move(uint8_t x, uint8_t y)
{
    if (cursor_visible)
        draw_cursor(x, y);

    print_mouse_coords(x, y);
}

void mouse_down(uint8_t button)
{
    if (button == LEFT)
        buttons[0] = true;

    if (button == MIDDLE)
        buttons[1] = true;

    if (button == RIGHT)
        buttons[2] = true;

    print_mouse_buttons();
}

void mouse_up(uint8_t button)
{
    if (button == LEFT)
        buttons[0] = false;

    if (button == MIDDLE)
        buttons[1] = false;

    if (button == RIGHT)
        buttons[2] = false;

    print_mouse_buttons();
}

void print_mouse_coords(uint8_t x, uint8_t y)
{
    char mouse_x_str[16] = "";
    int_to_ascii(x, mouse_x_str);

    char mouse_y_str[16] = "";
    int_to_ascii(y, mouse_y_str);

    char mouse_str[16] = "";
    strcat(mouse_str, mouse_x_str);
    strcat(mouse_str, " ");
    strcat(mouse_str, mouse_y_str);

    kprint_at_attr("        ", 0, 0, BLUE_ON_WHITE);
    kprint_at_attr(mouse_str, 0, 0, BLUE_ON_WHITE);
}

print_mouse_buttons()
{
    char mouse_str[16] = "";
    strcat(mouse_str, " | ");
    strcat(mouse_str, buttons[0] ? "1" : "0");
    strcat(mouse_str, buttons[1] ? "1" : "0");
    strcat(mouse_str, buttons[2] ? "1" : "0");
    kprint_at_attr("        ", 8, 0, BLUE_ON_WHITE);
    kprint_at_attr(mouse_str, 8, 0, BLUE_ON_WHITE);
}
