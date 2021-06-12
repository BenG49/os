# https://stackoverflow.com/questions/65099895/extended-inline-assembly-in-c-what-exactly-are-the-clobbered-registers
unsigned char port_byte_in(unsigned short port)
{
    unsigned char out;

    __asm__("in %0, %1"
           :"r"(port)
           :"=r"(out)
           :"%al");
}

void port_byte_out(unsigned char data, unsigned short port)
{

}

unsigned short port_word_in(unsigned short port)
{

}

void port_word_out(unsigned short data, unsigned short port)
{

}
