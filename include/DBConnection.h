#pragma once

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
    void getEntities(std::vector<Entity> &vec);

private:

    boost::asio::io_context _ctx;
    boost::asio::ssl::context _ssl_ctx;
    boost::mysql::tcp_ssl_connection _conn;

};