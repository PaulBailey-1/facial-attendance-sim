
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/mysql/tcp_ssl.hpp>

class DBConnection {
public:

    DBConnection();
    ~DBConnection();

    void test(); 

private:

    boost::asio::io_context _ctx;
    boost::asio::ssl::context _ssl_ctx{boost::asio::ssl::context::tls_client};
    boost::mysql::tcp_ssl_connection _conn;

};