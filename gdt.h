#ifndef __GDT_H
#define __GDT_H

#include "types.h"

  class GlobalDescriptorTable {
    public:
      class SegmentDescriptor {
        private:
          uint16_t limit_lo; // limit 2 bytes (low)
          uint16_t base_lo; // pointer 2 bytes (low)
          uint8_t base_hi; // another 1 byte for the pointer (high)
          uint8_t type; // access 1 byte
          uint8_t flags_limit_hi; // the lower 4 bits for limit_hi and the higher 4 bits for flags
          uint8_t base_vhi; // another 1 byte for the pointer

        public:
          SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
          uint32_t Base();
          uint32_t Limit();

      } __attribute__((packed));

      SegmentDescriptor nullSegmentSelector;
      SegmentDescriptor unusedSegmentSelector;
      SegmentDescriptor codeSegmentSelector;
      SegmentDescriptor dataSegmentSelector;

    public:
      GlobalDescriptorTable();
      ~GlobalDescriptorTable();

      uint16_t CodeSegmentSelector();
      uint16_t DataSegmentSelector();
  };

#endif
