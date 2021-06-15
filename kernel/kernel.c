#include "drivers/vga.h"

int main()
{
    clear();

    const char str[] = "This is a very long sentence and will eventually run off the page, this part of the sentence probably won't get printed";
    print(str, (BLACK << 4) | CYAN);
}
