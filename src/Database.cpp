
#include <stdexcept>

#include "Database.h"

Database::Database(char* url) {
 
    printf("Creating session on %s url ...", url);
    
    try {
        _session = new mysqlx::Session(url);
    } catch (const mysqlx::Error &e) {
        std::cout << "Failed to connect to database: " << e << "\n";
        throw std::runtime_error("Failed to connect to database\n");
    }

}

Database::~Database() {
    _session->close();
}