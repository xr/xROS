
#ifndef __XROS__HARDWARECOMMUNICATION__PCI_H
#define __XROS__HARDWARECOMMUNICATION__PCI_H

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>

namespace xros
{
   namespace hardwarecommunication
   {

       class PeripheralComponentInterconnectDeviceDescriptor
       {
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

           PeripheralComponentInterconnectDeviceDescriptor();
           ~PeripheralComponentInterconnectDeviceDescriptor();

       };


       class PeripheralComponentInterconnectController
       {
           Port32Bit dataPort;
           Port32Bit commandPort;

       public:
           PeripheralComponentInterconnectController();
           ~PeripheralComponentInterconnectController();

           xros::common::uint32_t Read(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function, xros::common::uint32_t registeroffset);
           void Write(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function, xros::common::uint32_t registeroffset, xros::common::uint32_t value);
           bool DeviceHasFunctions(xros::common::uint16_t bus, xros::common::uint16_t device);

           void SelectDrivers(xros::drivers::DriverManager* driverManager);
           PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(xros::common::uint16_t bus, xros::common::uint16_t device, xros::common::uint16_t function);
       };

   }
}

#endif
