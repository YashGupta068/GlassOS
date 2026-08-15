#include "screen.h"

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile unsigned char* video =
    (volatile unsigned char*)VGA_MEMORY;

static unsigned char color = 0x0F;

static int cursor_row = 0;
static int cursor_column = 0;

void screen_set_color(unsigned char new_color)
{
    color = new_color;
}

void screen_clear(void)
{
    for (int row = 0; row < VGA_HEIGHT; row++)
    {
        for (int column = 0; column < VGA_WIDTH; column++)
        {
            int index = (row * VGA_WIDTH + column) * 2;

            video[index] = ' ';
            video[index + 1] = color;
        }
    }

    cursor_row = 0;
    cursor_column = 0;
}

void screen_put_char(char character)
{
    if (character == '\n')
    {
        cursor_column = 0;
        cursor_row++;
        return;
    }

    int index =
        (cursor_row * VGA_WIDTH + cursor_column) * 2;

    video[index] = character;
    video[index + 1] = color;

    cursor_column++;

    if (cursor_column >= VGA_WIDTH)
    {
        cursor_column = 0;
        cursor_row++;
    }
}

void screen_print(const char* text)
{
    while (*text)
    {
        screen_put_char(*text);
        text++;
    }
}