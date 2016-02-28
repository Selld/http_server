#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>
#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "connectionhandler.h"

namespace HTTP {

using namespace boost::asio;

class HttpServer {
public:

    class HttpServerConfig
    {
    public:
        std::string host;
        std::string dir;
        uint16_t port;
        bool is_daemon;
    };
    HttpServerConfig config;

    static void create_instance(int argc, char * const *argv);
    static HttpServer* get_instance();
    void start_server();

private:
    io_service service;
    ip::tcp::endpoint ep;
    ip::tcp::acceptor accpt;
    HttpServer(const HttpServerConfig & cfg);
    void operator =(const HttpServer &s);
    void configure();
    static HttpServer *instance;
    ConnectionHandler *connection_handler;

    void handle_connection(std::shared_ptr<ip::tcp::socket> socket, const boost::system::error_code &error);
};

}


#endif // HTTPSERVER_H
