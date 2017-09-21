#ifndef __XROS__DRIVERS__MOUSE_H
#define __XROS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace xros {
  namespace drivers {
    class MouseEventHandler {
      public:
        MouseEventHandler();

        virtual void OnActivate();
        virtual void OnMouseDown(xros::common::uint8_t button);
        virtual void OnMouseUp(xros::common::uint8_t button);
        virtual void OnMouseMove(int x, int y);
    };

    class MouseDriver : public xros::hardwarecommunication::InterruptHandler, public Driver {
      xros::hardwarecommunication::Port8Bit dataport;
      xros::hardwarecommunication::Port8Bit commandport;

      xros::common::uint8_t buffer[3];
      xros::common::uint8_t offset;
      xros::common::uint8_t buttons;

      MouseEventHandler* handler;
      public:
        MouseDriver(xros::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
        ~MouseDriver();
        xros::common::uint32_t HandleInterrupt(xros::common::uint32_t esp);
        void Activate();
    };
  }
}

#endif
