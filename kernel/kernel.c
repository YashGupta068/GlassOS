#include "screen.h"

void kernel_main(void)
{
    screen_clear();

    screen_set_color(0x0F);

    screen_print("========================================\n");
    screen_print("          Welcome to GlassOS\n");
    screen_print("========================================\n\n");

    screen_print("GlassOS Kernel v0.3\n");
    screen_print("VGA Driver: OK\n");
    screen_print("Memory: OK\n");
    screen_print("System: Running\n");

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}