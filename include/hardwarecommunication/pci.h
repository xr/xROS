#ifndef __XROS__HARDWARECOMMUNICATION__PCI_H
#define __XROS__HARDWARECOMMUNICATION__PCI_H

#include <common/types.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>

namespace xros {
  namespace hardwarecommunication {

    enum BaseAddressRegisterType {
      MemoryMapping = 0,
      InputOutput = 1
    };

    class BaseAddressRegister {
      public:
        bool prefetchable;
        xros::common::uint8_t* address;
        xros::common::uint32_t size;
        BaseAddressRegisterType type;
    };

    class PCIDeviceDescriptor {
      public:
        xros::common::uint32_t portBase;
        xros::common::uint32_t interrupt;

        xros::common::uint16_t bus;
        xros::common::uint16_t device;
        xros::common::uint16_t function;

        xros::common::uint16_t vendor_id;
        xros::common::uint16_t device_id;

        xros::common::uint8_t class_id;
        xros::common::uint8_t subclass_id;
        xros::common::uint8_t interface_id;

        xros::common::uint8_t revision;

        PCIDeviceDescriptor();
        ~PCIDeviceDescriptor();
    };


    class PCIController {
      Port32Bit dataPort;
      Port32Bit commandPort;

      public:
        PCIController();
        ~PCIController();

        xros::common::uint32_t Read(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function, xros::common::uint32_t registeroffset);
        void Write(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function, xros::common::uint32_t registeroffset, xros::common::uint32_t value);

        bool DeviceHasFunctions(xros::common::uint16_t bus, xros::common::uint16_t device);

        void SelectDrivers(xros::drivers::DriverManager* driverManager, xros::hardwarecommunication::InterruptManager* interrupts);

        xros::drivers::Driver* GetDriver(PCIDeviceDescriptor, xros::hardwarecommunication::InterruptManager* interrupts);
        PCIDeviceDescriptor GetDeviceDescriptor(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function);
        BaseAddressRegister GetBaseAddressRegister(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function, xros::common::uint16_t bar);
    };
  }
}

#endif
