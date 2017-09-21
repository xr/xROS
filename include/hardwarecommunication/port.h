#ifndef __XROS__HARDWARECOMMUNICATION__PORT_H
#define __XROS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace xros {
  namespace hardwarecommunication {
    class Port {
      protected:
        xros::common::uint16_t portnumber;

        Port(xros::common::uint16_t portnumber);
        ~Port();
    };


    class Port8Bit : public Port {
      public:
        Port8Bit(xros::common::uint16_t portnumber);
        ~Port8Bit();
        virtual void Write(xros::common::uint8_t data);
        virtual xros::common::uint8_t Read();
    };

    class Port8BitSlow : public Port8Bit {
      public:
        Port8BitSlow(xros::common::uint16_t portnumber);
        ~Port8BitSlow();
        virtual void Write(xros::common::uint8_t data);
    };

    class Port16Bit : public Port {
      public:
        Port16Bit(xros::common::uint16_t portnumber);
        ~Port16Bit();
        virtual void Write(xros::common::uint16_t data);
        virtual xros::common::uint16_t Read();
    };

    class Port32Bit : public Port {
      public:
        Port32Bit(xros::common::uint32_t portnumber);
        ~Port32Bit();
        virtual void Write(xros::common::uint32_t data);
        virtual xros::common::uint32_t Read();
    };
  }
}

#endif
