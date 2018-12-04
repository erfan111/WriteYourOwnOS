#include <drivers/mouse.hpp>

using namespace wyoos::common;
using namespace wyoos::drivers;
using namespace wyoos::hardwarecommunication;

void printf(char*);

MouseEventHandler::MouseEventHandler()
{

}

void MouseEventHandler::OnActivate()
{

}

void MouseEventHandler::OnMouseDown(uint8_t)
{

}

void MouseEventHandler::OnMouseMove(int8_t, int8_t)
{

}

void MouseEventHandler::OnMouseUp(uint8_t)
{

}

MouseDriver::MouseDriver(InterruptManager* manager, MouseEventHandler *handler)
: InterruptHandler(manager, 0x2C),
dataport(0x60),
commandport(0x64)
{
    this->handler = handler;
}

MouseDriver::~MouseDriver()
{

}

void MouseDriver::Activate()
{
    offset = 0;
    buttons = 0;

    // handler->OnActivate();

    commandport.Write(0xA8); // Activate Interrupts
    commandport.Write(0x20); // Give Current State
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60); // Change state
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}

uint32_t MouseDriver::handleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();

    if(!(status & 0x20))
        return esp;
    if(handler == 0)
        return esp;

    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;

    if(offset == 0)
    {
        handler->OnMouseMove(buffer[1], -buffer[2]);

        for(uint8_t i = 0; i < 3; i++)
        {
            if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
            {
                if(buttons & (0x1<<i))
                    handler->OnMouseUp(i+1);
                else
                    handler->OnMouseDown(i+1);
            }
        }
        buttons = buffer[0];
        

    }

    return esp;
}