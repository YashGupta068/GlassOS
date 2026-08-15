#include "shell.h"
#include "screen.h"
#include "keyboard.h"

#define INPUT_SIZE 64

static char input[INPUT_SIZE];
static int input_length = 0;


/*
 * Reboot the computer.
 */
static void reboot_system(void)
{
    unsigned char good = 0x02;

    /*
     * Wait until keyboard controller is ready.
     */
    while (good & 0x02)
    {
        __asm__ volatile (
            "inb $0x64, %0"
            : "=a"(good)
        );
    }

    /*
     * Send reboot command.
     */
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"((unsigned char)0xFE),
          "Nd"((unsigned short)0x64)
    );

    /*
     * If reboot fails, halt.
     */
    while (1)
    {
        __asm__ volatile ("hlt");
    }
}


/*
 * Clear the input buffer.
 */
static void clear_input(void)
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        input[i] = '\0';
    }

    input_length = 0;
}


/*
 * Compare two strings.
 */
static int strings_equal(const char* a, const char* b)
{
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 0;
        }

        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}


/*
 * Execute the command entered by the user.
 */
static void execute_command(void)
{
    screen_print("\n");


    /*
     * HELP
     */
    if (strings_equal(input, "help"))
    {
        screen_print("Available commands:\n");

        screen_print("  help     - Show available commands\n");
        screen_print("  clear    - Clear the screen\n");
        screen_print("  version  - Show GlassOS version\n");
        screen_print("  about    - About GlassOS\n");
        screen_print("  echo     - Print text\n");
        screen_print("  reboot   - Restart GlassOS\n");
    }


    /*
     * VERSION
     */
    else if (strings_equal(input, "version"))
    {
        screen_print("GlassOS v0.6\n");
    }


    /*
     * ABOUT
     */
    else if (strings_equal(input, "about"))
    {
        screen_print("GlassOS - A custom operating system\n");
        screen_print("Built from scratch using Assembly and C\n");
    }


    /*
     * CLEAR
     */
    else if (strings_equal(input, "clear"))
    {
        screen_clear();
    }


    /*
     * ECHO
     *
     * Example:
     * echo Hello GlassOS
     */
    else if (input_length >= 5 &&
             input[0] == 'e' &&
             input[1] == 'c' &&
             input[2] == 'h' &&
             input[3] == 'o' &&
             input[4] == ' ')
    {
        screen_print(&input[5]);
        screen_print("\n");
    }


    /*
     * REBOOT
     */
    else if (strings_equal(input, "reboot"))
    {
        screen_print("Rebooting GlassOS...\n");

        reboot_system();
    }


    /*
     * EMPTY COMMAND
     */
    else if (input_length == 0)
    {
        /* Do nothing */
    }


    /*
     * UNKNOWN COMMAND
     */
    else
    {
        screen_print("Unknown command: ");
        screen_print(input);
        screen_print("\n");

        screen_print("Type 'help' for available commands.\n");
    }


    /*
     * Show prompt again.
     */
    screen_print("glass> ");

    clear_input();
}


/*
 * Start the GlassOS shell.
 */
void shell_run(void)
{
    clear_input();

    screen_print("glass> ");

    while (1)
    {
        char key = keyboard_get_char();


        /*
         * ENTER
         */
        if (key == '\n')
        {
            execute_command();
        }


        /*
         * BACKSPACE
         */
        else if (key == '\b')
        {
            if (input_length > 0)
            {
                input_length--;

                input[input_length] = '\0';

                screen_backspace();
            }
        }


        /*
         * NORMAL CHARACTER
         */
        else if (input_length < INPUT_SIZE - 1)
        {
            input[input_length] = key;
            input[input_length + 1] = '\0';

            input_length++;

            screen_put_char(key);
        }
    }
}