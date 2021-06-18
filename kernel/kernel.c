#include "kernel.h"

int kernel_main()
{
    init_idt();
    init_keyboard();
    init_timer(1);

    clear();
    puts("Type halt to halt and catch fire\n> ");

    return 0;
}

void shell_cmd(char *cmd)
{
    if (strcmp(cmd, "halt") == 0)
    {
        clear();
        puts("Sorry for wasting your time today!");
        asm("hlt");
    }
    else if (strcmp(cmd, "uptime") == 0)
    {
        int seconds = (int)get_seconds();
        int hours = seconds / 360;
        int minutes = seconds / 60;

        newline();
        putint(hours, 10);
        putchar(':');

        if (minutes < 10)
            putchar('0');
        putint(minutes, 10);
        putchar(':');

        if (seconds < 10)
            putchar('0');
        putint(seconds, 10);
    }
    else
    {
        puts("\n\"");
        puts(cmd);
        putchar('\"');
        puts(" is not a valid command.");
    }

    puts("\n> ");
}
