#ifndef __GDT_H
#define __GDT_H

#include "types.h"
// This table informs the CPU about different segments of codes
// It must be introduced to te CPU in the first steps of initialization
class GlobalDescriptorTable
{
public:
    // This class defines each row of the GlobalDescriptorTable
    class SegmentDescriptor
    {
    private:
        uint16_t limit_lo;  // end of the Segment address
        uint16_t base_lo;   // Start of the Segment address
        uint8_t base_hi;
        uint8_t type;
        uint8_t flags_limit_hi;
        uint8_t base_vhi;
    public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base();
        uint32_t Limit();
    };
    // Our GlobalDescriptorTable currently contains 4 entries:
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();

};





#endif //__GDT_H
