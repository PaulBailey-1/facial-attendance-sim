
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

        std::cout << "Connecting to mysql server at " << endpoints.begin()->endpoint() << std::endl;
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
    return true;
}

//void DBConnection::test() {
//    const char* sql = "SELECT num, message from test";
//    boost::mysql::results result;
//    _conn.execute(sql, result);
//
//    for (const boost::mysql::row_view &row : result.rows()) {
//        for (const boost::mysql::field_view &field : row) {
//            std::cout << field << " ";
//        }
//        std::cout << std::endl;
//    }
//}