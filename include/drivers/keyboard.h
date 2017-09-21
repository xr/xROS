#ifndef __XROS__DRIVERS__KEYBOARD_H
#define __XROS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace xros {
  namespace drivers {
    class KeyboardEventHandler {
      public:
        KeyboardEventHandler();

        virtual void OnKeyDown(char);
        virtual void OnKeyUp(char);
    };

    class KeyboardDriver : public xros::hardwarecommunication::InterruptHandler, public Driver {
      xros::hardwarecommunication::Port8Bit dataport;
      xros::hardwarecommunication::Port8Bit commandport;

      KeyboardEventHandler* handler;

      public:
        KeyboardDriver(xros::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler* handler);
        ~KeyboardDriver();
        xros::common::uint32_t HandleInterrupt(xros::common::uint32_t esp);
        void Activate();
    };
  }
}

#endif
