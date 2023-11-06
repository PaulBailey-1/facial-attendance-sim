#include <mysqlx/xdevapi.h>

class Database {
public:

    Database(char* url);
    ~Database();

private:

    mysqlx::Session* _session = nullptr;

};