#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include "../kernel/event_handlers.h"
#include "scancodes.h"
#include <stdint.h>

static void keyboard_callback(registers_t *regs)
{
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);

    if ((scancode & 0x7f) == LSHIFT)
    {
        shift_pressed = !(scancode >> 7);
        return;
    }

    if ((scancode & 0x7f) == CAPSLOCK && !(scancode >> 7))
    {
        caps_lock = !caps_lock;
        return;
    }

    if ((scancode & 0x7f) == BACKSPACE && !(scancode >> 7))
    {
        kprint_backspace();
        return;
    }

    char chr = decode_scancode(scancode & 0x7f);
    if (scancode >> 7)
        key_released(scancode, chr);
    else
        key_pressed(scancode, chr);

    // keyboard_input((int)scancode, ascii);

    // if (scancode == BACKSPACE) {
    //     backspace(key_buffer);
    //     kprint_backspace();
    // } else if (scancode == ENTER) {
    //     kprint("\n");
    //     keyboard_input(key_buffer); /* kernel-controlled function */
    //     key_buffer[0] = '\0';
    // } else {
    //     char letter = sc_ascii[(int)scancode];
    //     /* Remember that kprint only accepts char[] */
    //     char str[2] = {letter, '\0'};
    //     append(key_buffer, letter);
    //     kprint(str);
    // }
    
    UNUSED(regs);
}

char decode_scancode(uint8_t scancode)
{
    if (shift_pressed ^ caps_lock)
        return sc_caps_ascii[scancode];
    return sc_ascii[scancode];
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
