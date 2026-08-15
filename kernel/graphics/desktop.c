#include "desktop.h"
#include "graphics.h"

void desktop_draw(void)
{
    /*
     * Background
     */
    graphics_clear(0x111318);

    /*
     * Main glass panel
     */
    graphics_draw_rect(
        100,
        70,
        600,
        350,
        COLOR_GLASS
    );

    /*
     * Panel border
     */
    graphics_draw_border(
        100,
        70,
        600,
        350,
        2,
        0x667080
    );

    /*
     * Top bar
     */
    graphics_draw_rect(
        100,
        70,
        600,
        45,
        0x2B303A
    );

    /*
     * Terminal window
     */
    graphics_draw_rect(
        140,
        140,
        520,
        230,
        0x171A20
    );

    /*
     * Terminal border
     */
    graphics_draw_border(
        140,
        140,
        520,
        230,
        2,
        0x4A5260
    );
}