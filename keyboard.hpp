#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "port.hpp"
#include "interrupts.hpp"
#include "types.h"

class KeyboardDriver : public InterruptHandler
{
    Port8Bit dataport;
    Port8Bit commandport;
public:
    KeyboardDriver(InterruptManager* interruptManager);
    ~KeyboardDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);
};






#endif //__KEYBOARD_H
