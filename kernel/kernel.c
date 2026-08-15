#include "screen.h"
#include "keyboard.h"
#include "shell.h"

void kernel_main(void)
{
    screen_clear();

    screen_set_color(0x0F);

    screen_print("========================================\n");
    screen_print("             GlassOS v0.6\n");
    screen_print("========================================\n\n");

    screen_print("[ OK ] Kernel initialized\n");
    screen_print("[ OK ] VGA driver initialized\n");
    screen_print("[ OK ] Keyboard driver initialized\n");
    screen_print("[ OK ] Shell initialized\n\n");

    screen_print("Type 'help' to see available commands.\n\n");

    shell_run();

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}