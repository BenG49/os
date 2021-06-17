#include "kernel.h"

int kernel_main()
{
    init_idt();
    init_keyboard();
    init_timer(1);

    clear();
    print("Type halt to halt and catch fire\n> ");

    return 0;
}

void shell_cmd(char *cmd)
{
    if (streq(cmd, "halt"))
    {
        print("Sorry for wasting your time today!");
        asm("hlt");
    }
    else if (streq(cmd, "time"))
    {
        uint32_t time = get_seconds();

        newline();
        printi((int)time, 10, WOB);
        print(" seconds");
    }
    else
    {
        print("\n\"");
        print(cmd);
        printc('\"', WOB);
        print(" is not a valid command.");
    }

    print("\n> ");
}
