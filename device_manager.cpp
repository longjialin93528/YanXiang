//
// Created by long on 2018/5/25.
//
#include "device_manager.h"
device_manager::device_manager() {
    addDevice_ptr=NULL;
}
device_manager::device_manager(char *tbname) {
    addDevice_ptr=new sqlcon_add_device(tbname);
}
