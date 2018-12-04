#ifndef __WYOOS_HARDWARECOMMUNICATION_INTERRUPTS_H
#define __WYOOS_HARDWARECOMMUNICATION_INTERRUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.hpp>
#include <gdt.hpp>

namespace wyoos
{
    namespace hardwarecommunication
    {
        class InterruptManager;

        class InterruptHandler
        {
        protected:
            wyoos::common::uint8_t interrptNumber;
            InterruptManager* interruptManager;

            InterruptHandler(InterruptManager* interruptManager, wyoos::common::uint8_t interruptNumber);
            ~InterruptHandler();

        public:
            virtual wyoos::common::uint32_t handleInterrupt(wyoos::common::uint32_t esp);

        };


        class InterruptManager
        {
            friend class InterruptHandler;
        protected:

            static InterruptManager *ActiveInterruptManager;
            InterruptHandler* handlers[256];

            struct GateDescriptor
            {
                wyoos::common::uint16_t handlerAddressLowBits;
                wyoos::common::uint16_t gdt_codeSegmentSelector;
                wyoos::common::uint8_t reserved;
                wyoos::common::uint8_t access;
                wyoos::common::uint16_t handlerAddressHighBits;

            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct interruptDescriptorTablePointer
            {
                wyoos::common::uint16_t size;
                wyoos::common::uint32_t base;
            } __attribute__((packed));


            static void SetInterruptDescriptorTableEntry(wyoos::common::uint8_t interruptNumber,
                wyoos::common::uint16_t codeSegmentSelectorOffset,
                void (*handler)(),
                wyoos::common::uint8_t DescriptorPrivilageLevel,
                wyoos::common::uint8_t DescriptorType
            );

            wyoos::common::uint16_t hardwareInterruptOffset;

            Port8BitSlow picMasterCommand;
            Port8BitSlow picMasterData;
            Port8BitSlow picSlaveCommand;
            Port8BitSlow picSlaveData;

            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();

            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();

            static void InterruptIgnore();
            static wyoos::common::uint32_t handleInterrupt(wyoos::common::uint8_t interruptNumber, wyoos::common::uint32_t esp);
            wyoos::common::uint32_t DoHandleInterrupt(wyoos::common::uint8_t interruptNumber, wyoos::common::uint32_t esp);

        public:
            InterruptManager(wyoos::common::uint16_t hardwareInterruptOffset, GlobalDescriptorTable* gdt);
            ~InterruptManager();
            wyoos::common::uint16_t HardwareInterruptOffset();
            void Activate();
            void Deactivate();

        };

    }
}


#endif
