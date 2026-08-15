#include "graphics.h"

static framebuffer_t framebuffer;

void graphics_init(void)
{
    framebuffer.address = 0;
    framebuffer.width = 0;
    framebuffer.height = 0;
    framebuffer.pitch = 0;
    framebuffer.bpp = 0;
}

void graphics_put_pixel(
    uint32_t x,
    uint32_t y,
    uint32_t color
)
{
    if (framebuffer.address == 0)
        return;

    if (x >= framebuffer.width ||
        y >= framebuffer.height)
        return;

    uint32_t index =
        y * (framebuffer.pitch / 4) + x;

    framebuffer.address[index] = color;
}

void graphics_clear(uint32_t color)
{
    if (framebuffer.address == 0)
        return;

    for (uint32_t y = 0;
         y < framebuffer.height;
         y++)
    {
        for (uint32_t x = 0;
             x < framebuffer.width;
             x++)
        {
            graphics_put_pixel(x, y, color);
        }
    }
}

void graphics_draw_rect(
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    uint32_t color
)
{
    for (uint32_t row = 0;
         row < height;
         row++)
    {
        for (uint32_t column = 0;
             column < width;
             column++)
        {
            graphics_put_pixel(
                x + column,
                y + row,
                color
            );
        }
    }
}

void graphics_draw_border(
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    uint32_t thickness,
    uint32_t color
)
{
    graphics_draw_rect(
        x,
        y,
        width,
        thickness,
        color
    );

    graphics_draw_rect(
        x,
        y + height - thickness,
        width,
        thickness,
        color
    );

    graphics_draw_rect(
        x,
        y,
        thickness,
        height,
        color
    );

    graphics_draw_rect(
        x + width - thickness,
        y,
        thickness,
        height,
        color
    );
    void graphics_set_framebuffer(
    uint32_t* address,
    uint32_t width,
    uint32_t height,
    uint32_t pitch,
    uint8_t bpp
)
{
    framebuffer.address = address;
    framebuffer.width = width;
    framebuffer.height = height;
    framebuffer.pitch = pitch;
    framebuffer.bpp = bpp;
}
}