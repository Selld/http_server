#include <iostream>
#include "httpserver.h"

int main(int argc, char* const *argv)
{
    HTTP::HttpServer::create_instance(argc, argv);
    HTTP::HttpServer *server = HTTP::HttpServer::get_instance();
    server->start_server();
    return 0;
}

