#ifndef __XROS__GDT_H
#define __XROS__GDT_H

#include <common/types.h>

namespace xros {
  class GlobalDescriptorTable {
    public:
      class SegmentDescriptor {
        private:
          xros::common::uint16_t limit_lo; // limit 2 bytes (low)
          xros::common::uint16_t base_lo; // pointer 2 bytes (low)
          xros::common::uint8_t base_hi; // another 1 byte for the pointer (high)
          xros::common::uint8_t type; // access 1 byte
          xros::common::uint8_t flags_limit_hi; // the lower 4 bits for limit_hi and the higher 4 bits for flags
          xros::common::uint8_t base_vhi; // another 1 byte for the pointer

        public:
          SegmentDescriptor(xros::common::uint32_t base, xros::common::uint32_t limit, xros::common::uint8_t type);
          xros::common::uint32_t Base();
          xros::common::uint32_t Limit();

      } __attribute__((packed));

      SegmentDescriptor nullSegmentSelector;
      SegmentDescriptor unusedSegmentSelector;
      SegmentDescriptor codeSegmentSelector;
      SegmentDescriptor dataSegmentSelector;

    public:
      GlobalDescriptorTable();
      ~GlobalDescriptorTable();

      xros::common::uint16_t CodeSegmentSelector();
      xros::common::uint16_t DataSegmentSelector();
  };
}

#endif
