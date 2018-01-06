#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.hpp"
#include "gdt.hpp"

// This class initializes the interrupt handling in CPU by defining the interrupt descriptor table and feeding it to CPU
class InterruptManager
{
protected:
    // each GateDescriptor is an entry in interruptDescriptorTable
    struct GateDescriptor
    {
        uint16_t handlerAddressLowBits; // Address of the handler
        uint16_t gdt_codeSegmentSelector;   // address of the code segment of the handler
        uint8_t reserved;
        uint8_t access;     // access rights
        uint16_t handlerAddressHighBits;

    } __attribute__((packed));  // do not optimize or change the place of attributes in RAM: provide it as is
    // Our interrupt table contains 256 rows
    static GateDescriptor interruptDescriptorTable[256];
    // the pointer to our table which is passed to CPU
    struct interruptDescriptorTablePointer
    {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));

    // Create an entry in interrupt table
    static void SetInterruptDescriptorTableEntry(uint8_t interruptNumber,
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),
        uint8_t DescriptorPrivilageLevel,
        uint8_t DescriptorType
    );
    // 0x20 added to all the interrupt numbers
    uint16_t hardwareInterruptOffset;
    // we have to define the ports through which we talk to the interrupt controllers, we have 2 controllers
    Port8BitSlow picMasterCommand;
    Port8BitSlow picMasterData;
    Port8BitSlow picSlaveCommand;
    Port8BitSlow picSlaveData;
    // interrupt and exception handlers defined
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
    // the routine which does nothing if interrupt occures
    static void InterruptIgnore();
    // this is the commander which invokes the above handlers, itself is invoked by assembly interruptstubs.s
    static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);

public:
    InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* gdt);
    ~InterruptManager();
    uint16_t HardwareInterruptOffset();
    void Activate();

};

#endif
