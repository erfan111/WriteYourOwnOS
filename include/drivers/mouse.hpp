#ifndef __WYOOS_DRIVERS_MOUSE_H
#define __WYOOS_DRIVERS_MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.hpp>
#include <hardwarecommunication/port.hpp>
#include <drivers/driver.hpp>


namespace wyoos
{
    namespace drivers
    {

        class MouseEventHandler
        {
        public:

            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseUp(wyoos::common::uint8_t button);
            virtual void OnMouseDown(wyoos::common::uint8_t button);
            virtual void OnMouseMove(wyoos::common::int8_t x, wyoos::common::int8_t y);

        };

        class MouseDriver : public wyoos::hardwarecommunication::InterruptHandler, public Driver
        {
            wyoos::hardwarecommunication::Port8Bit dataport;
            wyoos::hardwarecommunication::Port8Bit commandport;

            wyoos::common::uint8_t buffer[3];
            wyoos::common::uint8_t offset;
            wyoos::common::uint8_t buttons;

            MouseEventHandler *handler;


        public:
            MouseDriver(wyoos::hardwarecommunication::InterruptManager* manager, MouseEventHandler *handler);
            ~MouseDriver();
            virtual wyoos::common::uint32_t handleInterrupt(wyoos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}


#endif //__MOUSE_H