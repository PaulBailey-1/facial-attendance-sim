#pragma once

#include <boost/core/span.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/mysql/tcp_ssl.hpp>

#include "Entity.h"

class DBConnection {
public:

    DBConnection();
    ~DBConnection();

    bool connect();
    bool query(const char* sql, boost::mysql::results& result);
    
    void createTables();
    void getEntities(std::vector<Entity*> &vec);
    void pushUpdate(int devId, const boost::span<UCHAR> facialFeatures);

private:

    boost::asio::io_context _ctx;
    boost::asio::ssl::context _ssl_ctx;
    boost::mysql::tcp_ssl_connection _conn;

};