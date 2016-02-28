#include <thread>

#include <iostream>

#include "connectionhandler.h"
#include "http_request.h"
#include "http_response.h"

using namespace HTTP;

ConnectionHandler::ConnectionHandler()
{
}

void ConnectionHandler::process_connection(std::shared_ptr<ip::tcp::socket> connection)
{
    try {
        std::thread worker([connection, this] () {
            this->handle_connection(connection);
        } );
        worker.detach();
    } catch(boost::system::system_error & e) {
        std::cout << e.code() << std::endl;
    }
}

void ConnectionHandler::handle_connection(std::shared_ptr<ip::tcp::socket> connection) {
    char buff[MAX_INPUT_SIZE];
    size_t size = connection->read_some(buffer(buff, MAX_INPUT_SIZE));
    buff[size] = '\0';

    HTTP_Request request(buff);
    HTTP_Response response = request.do_request();
    std::string raw_resp = response.to_string();

    connection->write_some(buffer(raw_resp.c_str(), raw_resp.length()));

    connection->close();
}
