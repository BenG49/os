void dummy_test_entrypoint() {}

int main()
{
    char *vga_mem = (char*)0xb8000;
    char *str = "test";
    char *str_ptr = str;

    char current = *str_ptr;
    while (current != '\0')
    {
        *vga_mem = current;
        vga_mem += 2;
        ++str_ptr;
        current = *str_ptr;
    }
}
