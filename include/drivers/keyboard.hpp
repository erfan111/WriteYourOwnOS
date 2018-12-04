#ifndef __WYOOS_DRIVERS_KEYBOARD_H
#define __WYOOS_DRIVERS_KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.hpp>
#include <hardwarecommunication/port.hpp>
#include <drivers/driver.hpp>

namespace wyoos
{
    namespace drivers
    {

        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyUp(char);
            virtual void OnKeyDown(char);

        };

        class KeyboardDriver : public wyoos::hardwarecommunication::InterruptHandler, public Driver
        {
            wyoos::hardwarecommunication::Port8Bit dataport;
            wyoos::hardwarecommunication::Port8Bit commandport;

            KeyboardEventHandler* handler;

        public:
            KeyboardDriver(wyoos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler* handler);
            ~KeyboardDriver();
            virtual wyoos::common::uint32_t handleInterrupt(wyoos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}


#endif //__KEYBOARD_H