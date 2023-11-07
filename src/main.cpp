#include <iostream>

#include <boost/mysql/error_with_diagnostics.hpp>

#include "Device.h"
#include "DBConnection.h"

int main() {

    try {
        DBConnection db; 
        db.test();
    }
    catch (const boost::mysql::error_with_diagnostics& err) {
        std::cerr << "Error: " << err.what() << '\n'
            << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
        return 1;
    }
    catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }

    
    //Device* dev = new Device();
    //dev.run();

    return 0;
}

// todo
// I need to add simulated updates to a sql server 
