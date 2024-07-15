#include <print.h>

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char
{
    uint8_t chr;
    uint8_t color;
};

struct Char *buffer = (struct Char *)0xB8000;
size_t col = 0, row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row)
{
    struct Char empty = (struct Char){
        chr : ' ',
        color : color
    };

    for (size_t col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear()
{
    for (size_t row = 0; row < NUM_ROWS; row++)
    {
        clear_row(row);
    }
}

void print_newline()
{
    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++)
    {
        for (size_t col = 0; col < NUM_COLS; col++)
        {
            struct Char chr = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = chr;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char chr)
{
    if (chr == '\n')
    {
        print_newline();
        return;
    }

    if (col > NUM_COLS)
    {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char){
        chr : (uint8_t)chr,
        color : color
    };

    col++;
}

void print_str(char *str)
{
    for (size_t i = 0; 1; i++)
    {
        char chr = (uint8_t)str[i];

        if (chr == '\0')
        {
            return;
        }

        print_char(chr);
    }
}

void print_set_color(uint8_t foreground, uint8_t background)
{
    color = foreground + (background << 4);
}