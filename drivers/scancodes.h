#pragma once

#define ESC 0x01
#define BACKSPACE 0x0e
#define ENTER 0x1c

#define LSHIFT 0x2a
#define LSHIFT_RELEASE 0xaa
#define RSHIFT 0x36
#define LCTRL 0x1d
#define CAPSLOCK 0x3a
#define NUMLOCK 0x45
#define SCROLLOCK 0x46


#define SC_MAX 84

const char* sc_shift_name[] = {
    "ERROR", "Esc", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace", "Tab",
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "Enter", "Lctrl", 
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "~", "LShift", "|",
    "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
    "Rshift", "Keypad-*", "LAlt", "Space", "Caps Lock",
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", 
    "Num lock", "Scroll lock",
    "Keypad-7", "Keypad-8", "Keypad-9", "Keypad--", "Keypad-4", "Keypad-5", "Keypad-6",
    "Keypad-+", "Keypad-1", "Keypad-2", "Keypad-3", "Keypad-0", "Keypad-."
};

const char *sc_normal_name[] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "Enter", "Lctrl", 
    "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "\'", "`", "LShift", "\\",
    "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
    "Rshift", "Keypad-*", "LAlt", "Space", "Caps Lock",
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", 
    "Num lock", "Scroll lock",
    "Keypad-7", "Keypad-8", "Keypad-9", "Keypad--", "Keypad-4", "Keypad-5", "Keypad-6",
    "Keypad-+", "Keypad-1", "Keypad-2", "Keypad-3", "Keypad-0", "Keypad-."
};

const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '?', '?',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '?', '?', 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    '?', '*', '?', ' ', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 
    '?', '?',
    '7', '8', '9', '-', '4', '5', '6',
    '+', '1', '2', '3', '0', '.'
};

const char sc_caps_ascii[] = {
    '?', '?', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '?', '?',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '?', '?', 
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\'', '~', '?', '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    '?', '*', '?', ' ', '?',
    '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 
    '?', '?',
    '7', '8', '9', '-', '4', '5', '6',
    '+', '1', '2', '3', '0', '-.'
};
