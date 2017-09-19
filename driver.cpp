#include "driver.h"

Driver::Driver() {

}

Driver::~Driver() {

}

void Driver::Activate() {

}

int Driver::Reset() {
  return 0;
}

void Driver::Deactivate() {

}


DriverManager::DriverManager() {
  numDrivers = 0;
}

void AddDriver(Driver* drv) {
  drivers[numDrivers] = drv;
  numDrivers++;
}
