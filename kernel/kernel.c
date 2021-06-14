#include "drivers/vga.h"

int main()
{
    clear();
    char a[5] = "owov\0";
    print(a);
}
