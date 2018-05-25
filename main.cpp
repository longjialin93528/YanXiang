#include "device_modbus.h"
int main() {

    Modbus_device * ptr_device=new Modbus_device();
    ptr_device->run();
    ptr_device->show_humidity();
    ptr_device->show_temperature();

    return 0;
}