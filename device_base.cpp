//
// Created by long on 2018/5/18.
//
#include "device_base.h"
Base_device::Base_device() {
    deviceID=0;
    deviceType=NONE;
    deviceAddress=0;
}
Base_device::Base_device(unsigned int id) {
    deviceID=id;
    deviceAddress=id;
    deviceType=NONE;
}
Base_device::~Base_device() {

}
unsigned int Base_device::get_deviceID() {
    return deviceID;
}
void Base_device::set_deviceID(unsigned int id) {
    deviceID=id;
    deviceAddress=id;
}
device_type Base_device::get_deviceType() {
    return deviceType;
}
void Base_device::set_deviceType(device_type type) {
    deviceType=type;
}
unsigned int Base_device::get_deviceAddress() {
    return deviceAddress;
}
