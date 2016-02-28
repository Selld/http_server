#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <memory>
#include <boost/asio.hpp>

namespace HTTP {

using namespace boost::asio;

class ConnectionHandler
{
public:
    ConnectionHandler();
    void process_connection(std::shared_ptr<ip::tcp::socket> connection);
private:
    static const int MAX_INPUT_SIZE = 500;
    void handle_connection(std::shared_ptr<ip::tcp::socket> connection);
};
}
#endif // CONNECTIONHANDLER_H
