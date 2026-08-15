#include "shell.h"
#include "screen.h"
#include "keyboard.h"

#define INPUT_SIZE 64

static char input[INPUT_SIZE];
static int input_length = 0;

static void clear_input(void)
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        input[i] = '\0';
    }

    input_length = 0;
}

static int strings_equal(const char* a, const char* b)
{
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
            return 0;

        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

static void execute_command(void)
{
    screen_print("\n");

    if (strings_equal(input, "help"))
    {
        screen_print("Available commands:\n");
        screen_print("  help\n");
        screen_print("  clear\n");
        screen_print("  version\n");
        screen_print("  about\n");
        screen_print("  echo\n");
    }
    else if (strings_equal(input, "version"))
    {
        screen_print("GlassOS v0.5\n");
    }
    else if (strings_equal(input, "about"))
    {
        screen_print("GlassOS - A custom operating system\n");
        screen_print("Built from scratch with Assembly and C\n");
    }
    else if (strings_equal(input, "clear"))
    {
        screen_clear();
    }
    else if (strings_equal(input, "echo"))
    {
        screen_print("Echo command ready.\n");
    }
    else if (input_length == 0)
    {
        /* Do nothing */
    }
    else
    {
        screen_print("Unknown command.\n");
        screen_print("Type 'help' for available commands.\n");
    }

    screen_print("glass> ");
    clear_input();
}

void shell_run(void)
{
    clear_input();

    screen_print("glass> ");

    while (1)
    {
        char key = keyboard_get_char();

        if (key == '\n')
        {
            execute_command();
        }
        else if (input_length < INPUT_SIZE - 1)
        {
            input[input_length] = key;
            input_length++;

            screen_put_char(key);
        }
    }
}