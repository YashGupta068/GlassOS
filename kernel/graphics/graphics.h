#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef struct
{
    uint32_t* address;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint8_t bpp;
} framebuffer_t;

void graphics_init(void);

void graphics_put_pixel(
    uint32_t x,
    uint32_t y,
    uint32_t color
);

void graphics_clear(uint32_t color);

void graphics_draw_rect(
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    uint32_t color
);

void graphics_draw_border(
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    uint32_t thickness,
    uint32_t color
);
void graphics_set_framebuffer(
    uint32_t* address,
    uint32_t width,
    uint32_t height,
    uint32_t pitch,
    uint8_t bpp
);
#define COLOR_BLACK  0x000000
#define COLOR_WHITE  0xFFFFFF
#define COLOR_GRAY   0x808080
#define COLOR_BLUE   0x3366FF
#define COLOR_GLASS  0x20242C

#endif