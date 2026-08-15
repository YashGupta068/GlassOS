#include "screen.h"
#include "keyboard.h"
#include "shell.h"
#include "graphics/graphics.h"

void kernel_main(void)
{
    screen_clear();

    screen_set_color(0x0F);

    screen_print("========================================\n");
    screen_print("             GlassOS v0.7\n");
    screen_print("========================================\n\n");

    screen_print("[ OK ] Kernel initialized\n");
    screen_print("[ OK ] VGA driver initialized\n");
    screen_print("[ OK ] Keyboard driver initialized\n");
    screen_print("[ OK ] Shell initialized\n");
    screen_print("[ OK ] Graphics engine initialized\n\n");

    graphics_init();

    screen_print("Graphics framebuffer: waiting\n\n");

    screen_print("Type 'help' to enter the shell.\n\n");

    shell_run();

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}