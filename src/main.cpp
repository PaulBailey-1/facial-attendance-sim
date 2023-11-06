#include <iostream>

#include "Device.h"
#include "Database.h"

int main() {

    try {
        Database db("mysqlx://root@127.0.0.1");
    } catch (...) {
        return 1;
    }
    
    Device* dev = new Device();
    dev.run();

    return 0;
}

// todo
// I need to add simulated updates to a sql server 