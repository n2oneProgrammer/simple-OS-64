#pragma once

#include "IO.cpp"
#include "Typedef.cpp"
#include "TextModeColorCodes.cpp"

#define VGA_MEMORY (uint_8*)0xb8000
#define VGA_WIDTH 80
uint_16 cursorPosition;

void ClearScreen(uint_64 color = FOREGROUND_WHITE | BACKGROUND_BLUE) {
    uint_64 value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;
    for (uint_64 *i = (uint_64 *) VGA_MEMORY; i < (uint_64 *) (VGA_MEMORY + 4000); i++) {
        *i = value;
    }
}

void SetCursorPosition(uint_16 position) {
    if (position > 2000) position = 2000;
    if (position < 0) position = 0;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint_8) (position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8) ((position >> 8) & 0xFF));

    cursorPosition = position;


}

void ResetCursor() {
    SetCursorPosition(0);
}

uint_16 PositionFromCoords(uint_8 x, uint_8 y) {
    return y * VGA_WIDTH + x;
}

void PrintString(const char *str, uint_16 color = FOREGROUND_WHITE | BACKGROUND_BLUE) {
    uint_8 *charPtr = (uint_8 *) str;
    uint_16 index = cursorPosition;
    while (*charPtr != 0) {

        switch (*charPtr) {
            case '\n':
                index += VGA_WIDTH;
                break;
            case '\r':
                index = (index / VGA_WIDTH) * VGA_WIDTH;
                break;
            default:
                *(VGA_MEMORY + index * 2) = *charPtr;
                *(VGA_MEMORY + index * 2 + 1) = color;
                index++;
        }
        charPtr++;
    }
    SetCursorPosition(index);
}

void PrintChar(char chr, uint_16 color = FOREGROUND_WHITE | BACKGROUND_BLUE) {
    *(VGA_MEMORY + cursorPosition * 2) = chr;
    *(VGA_MEMORY + cursorPosition * 2 + 1) = color;
    SetCursorPosition(cursorPosition + 1);
}


char hexToStringOut[128];

template<typename T>
const char *Hex2String(T value) {
    T *valPtr = &value;
    uint_8 *ptr;
    uint_8 temp;
    uint_8 size = (sizeof(T)) * 2 - 1;
    for (uint_8 i = 0; i < size; i++) {
        ptr = ((uint_8 *) valPtr + i);
        temp = ((*ptr & 0xF0) >> 4);
        hexToStringOut[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = (*ptr & 0x0F);
        hexToStringOut[size - (i * 2)] = temp + (temp > 9 ? 55 : 48);
    }
    hexToStringOut[size + 1] = 0;
    return hexToStringOut;
}
