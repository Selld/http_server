#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <stdexcept>
#include <vector>

#include "http_status_codes.h"
#include "http_response.h"

class HTTP_Request
{
public:

    enum HTTP_Method {
        GET
    };

    HTTP_Request(const char *buff);
    HTTP_Response do_request();
private:
    HTTP_Method method;
    std::string uri;
    std::string args;
    std::string HTTP_version;
    u_int32_t flags;

    static const u_int32_t BAD_REQUEST = 1;
    static const u_int32_t NOT_FOUND = 2;

    static const size_t METHOD_POS = 0;
    static const size_t URI_POS = 1;
    static const size_t PROTO_POS = 2;

    HTTP_Method parse_method(const std::vector<std::string> & tokens);
    std::string parse_uri(const std::vector<std::string> & tokens);
    std::string parse_version(const std::vector<std::string> & tokens);
};

class BadRequestException : public std::logic_error
{
public:
    BadRequestException(const char* what_arg);
    BadRequestException(const std::string& what_arg);
};

#endif // HTTP_REQUEST_H
