#include "drivers/vga.h"

int main()
{
    clear();

    char buf[1] = "a";
    for (int i = 0; i < 24; ++i)
    {
        set_cursor_pos(0, i);
        print(buf, (BLACK << 4) | (i % WHITE));
        ++buf[0];
    }

    set_cursor_pos(0, 24);
    const char str[] = "This is a very long sentence and will eventually run off the page, this part of the sentence probably won't get printed";
    print(str, (BLACK << 4) | CYAN);
}
