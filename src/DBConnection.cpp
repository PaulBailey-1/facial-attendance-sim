
#include <iostream>

#include <boost/mysql/error_with_diagnostics.hpp>
#include <boost/mysql/handshake_params.hpp>
#include <boost/mysql/results.hpp>
#include <boost/system/system_error.hpp>

#include "DBConnection.h"

DBConnection::DBConnection() : _ssl_ctx(boost::asio::ssl::context::tls_client), _conn(_ctx, _ssl_ctx) {}

DBConnection::~DBConnection() {
    _conn.close();
}

bool DBConnection::connect() {
    try {
        boost::asio::ip::tcp::resolver resolver(_ctx.get_executor());
        auto endpoints = resolver.resolve("127.0.0.1", boost::mysql::default_port_string);
        boost::mysql::handshake_params params("root", "", "test", boost::mysql::handshake_params::default_collation, boost::mysql::ssl_mode::enable);

        std::cout << "Connecting to mysql server at " << endpoints.begin()->endpoint() << " ... " << std::endl;
        _conn.connect(*endpoints.begin(), params);
    }
    catch (const boost::mysql::error_with_diagnostics& err) {
        std::cerr << "Error: " << err.what() << '\n'
            << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
        return false;
    }
    catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return false;
    }
    std::cout << "Connected\n";
    return true;
}

bool DBConnection::query(const char* sql, boost::mysql::results &result) {
    try {
        _conn.execute(sql, result);
    }
    catch (const boost::mysql::error_with_diagnostics& err) {
        std::cerr << "Error: " << err.what() << '\n'
            << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
        return false;
    }
    catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return false;
    }
    return true;
}

void DBConnection::createTables() {
    boost::mysql::results r;
    query("CREATE TABLE IF NOT EXISTS Students (\
        id INT AUTO_INCREMENT PRIMARY KEY, \
        fromRoom INT, \
        toRoom INT \
    )", r);
}

void DBConnection::getEntities(std::vector<Entity> &vec) {
    boost::mysql::results result;
    if (query("SELECT id, fromRoom, toRoom from Students", result) && !result.empty()) {
        for (const boost::mysql::row_view& row : result.rows()) {
            vec.push_back(Entity(row.at(0).as_int64(), row.at(1).as_int64(), row.at(2).as_int64()));
        }
    }
}