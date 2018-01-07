#include "keyboard.hpp"

KeyboardDriver::KeyboardDriver(InterruptManager* interruptManager)
: InterruptHandler(0x21, interruptManager),
dataport(0x60),
commandport(0x64)
{
}

KeyboardDriver::~KeyboardDriver()
{
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    
    char* foo = "KEYBOARD 0x00";
    char* hex = "0123456789ABCDEF";
    foo[11] = hex[(key >> 4) & 0xF];
    foo[12] = hex[key & 0xF];
    printf(foo);
    return esp;
}
