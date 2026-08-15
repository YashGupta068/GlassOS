#include "screen.h"
#include "keyboard.h"
#include "shell.h"

void kernel_main(void)
{
    screen_clear();

    screen_set_color(0x0F);

    screen_print("========================================\n");
    screen_print("          Welcome to GlassOS\n");
    screen_print("========================================\n\n");

    screen_print("GlassOS v0.5\n");
    screen_print("Kernel: OK\n");
    screen_print("VGA Driver: OK\n");
    screen_print("Keyboard Driver: OK\n");
    screen_print("Shell: OK\n\n");

    shell_run();

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}