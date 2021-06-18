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
    else if (strcmp(cmd, "time") == 0)
    {
        uint32_t time = get_seconds();

        newline();
        putint((int)time, 10);
        puts(" seconds");
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
