#ifndef __XROS__HARDWARECOMMUNICATION__INTERRUPTS_H
#define __XROS__HARDWARECOMMUNICATION__INTERRUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>


namespace xros {
  namespace hardwarecommunication {
    class InterruptManager;

    class InterruptHandler {
      protected:
        xros::common::uint8_t interruptNumber;
        InterruptManager* interruptManager;

        InterruptHandler(xros::common::uint8_t interruptNumber, InterruptManager* interruptManager);
        ~InterruptHandler();
      public:
        virtual xros::common::uint32_t HandleInterrupt(xros::common::uint32_t esp);
    };

    class InterruptManager {
      friend class InterruptHandler;
      protected:
        static InterruptManager* ActiveInterruptManager;
        InterruptHandler* handlers[256];

        struct GateDescriptor {
          xros::common::uint16_t handlerAddressLowBits;
          xros::common::uint16_t gdt_codeSegmentSelector;
          xros::common::uint8_t reserved;
          xros::common::uint8_t access;
          xros::common::uint16_t handlerAddressHighBits;

        } __attribute__((packed));

        static GateDescriptor interruptDescriptorTable[256];

        struct InterruptDescriptorTablePointer {
          xros::common::uint16_t size;
          xros::common::uint32_t base;
        } __attribute__((packed));

        static void SetInterruptDescriptorTableEntry(
          xros::common::uint8_t interruptNumber,
          xros::common::uint16_t codeSegmentSelectorOffset,
          void (*handler)(),
          xros::common::uint8_t DescriptorPrivilegeLevel,
          xros::common::uint8_t DescriptorType
        );

        Port8BitSlow picMasterCommand;
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveCommand;
        Port8BitSlow picSlaveData;


      public:
        InterruptManager(xros::GlobalDescriptorTable* gdt);
        ~InterruptManager();

        void Activate();
        void Deactivate();

        static xros::common::uint32_t handleInterrupt(xros::common::uint8_t interruptNumber, xros::common::uint32_t esp);
        xros::common::uint32_t DohandleInterrupt(xros::common::uint8_t interruptNumber, xros::common::uint32_t esp);

        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
        static void HandleInterruptRequest0x0C();
    };
  }
}

#endif
