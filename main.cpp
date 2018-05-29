#include "device_manager.h"
int main() {
    device_manager * ptr=new device_manager("device_info");
    ptr->run();
    return 0;
}