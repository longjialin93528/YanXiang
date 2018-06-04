cmake_minimum_required(VERSION 3.9)
project(YanXiang)

set(CMAKE_CXX_STANDARD 11)

add_executable(YanXiang main.cpp value_type.h device_base.h device_base.cpp device_modbus.cpp device_modbus.h sqlcon_base.h sqlcon_base.cpp sqlcon_add_device.h sqlcon_add_device.cpp device_manager.h device_manager.cpp sqlcon_modbus_pm.h sqlcon_modbus_pm.cpp device_modbus_pm.h device_modbus_pm.cpp sqlcon_dido.h sqlcon_dido.cpp device_dido.h device_dido.cpp device_modbus_th.h device_modbus_th.cpp sqlcon_modbus_th.cpp sqlcon_modbus_th.h)