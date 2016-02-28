#include <cstdlib>
#include <unistd.h>
// #include <fstream>

#include "httpserver.h"

void sighup_handler(int x) {
    sleep(10);
}

using namespace HTTP;

HttpServer* HttpServer::instance = nullptr;

HttpServer::HttpServer(const HttpServerConfig &cfg) :
    config(cfg),
    ep(ip::address_v4::from_string(cfg.host), cfg.port),
    accpt(service, ep)
{
    connection_handler = new ConnectionHandler();
}

void HttpServer::handle_connection(std::shared_ptr<ip::tcp::socket> sock, const boost::system::error_code& error) {
    connection_handler->process_connection(sock);
    std::shared_ptr<ip::tcp::socket> new_sock(new ip::tcp::socket(service));
    accpt.async_accept(*new_sock, boost::bind(&HttpServer::handle_connection, this, new_sock, _1));
}

void HttpServer::start_server(){


    std::shared_ptr<ip::tcp::socket> sock(new ip::tcp::socket(service));
    accpt.async_accept(*sock, boost::bind(&HttpServer::handle_connection, this, sock, _1));

    if (!fork()) {
        sleep(10);
        umask(0);
        signal(SIGHUP, sighup_handler);
        setsid();
    } else {
        sleep(10);
        exit(0);
    }
    sleep(15);
    service.run();

}

void HttpServer::create_instance(int argc, char* const *argv) {
    HttpServerConfig cfg;

    const int DIR_ARG = 1;
    const int HOST_ARG = 2;
    const int PORT_ARG = 4;

    int res_status = 0;

    int arg_flags = 0;

    while((res_status = getopt(argc, argv, "h:p:d:")) != -1) {
        switch(res_status){
            case 'h': {
                cfg.host = optarg;
                arg_flags |= HOST_ARG;
                break;
            }
            case 'p': {
                cfg.port = (uint16_t)atoi(optarg);
                arg_flags |= PORT_ARG;
                break;
            }
            case 'd': {
                cfg.dir = optarg;
                arg_flags |= DIR_ARG;
                break;
            }
            case '?': {
                exit(1);
            }
        }
    }

    if (!(arg_flags & (DIR_ARG | HOST_ARG | PORT_ARG) )) {
        // std::cerr << "Wrong input args" << std::endl;
        exit(1);
    }
    instance = new HttpServer(cfg);
}

HttpServer *HttpServer::get_instance()
{
    if (instance == nullptr) {
        //std::cerr << "instance not created @get_instance" << std::endl;
    }
    return instance;
}

