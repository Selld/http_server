#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include <memory>
#include "http_status_codes.h"
#include "content_type.h"

#define HTTP_VERSION "HTTP/1.0"

class HTTP_Response
{
public:
    HTTP_Response(HTTP_StatusCode status);
    HTTP_Response(HTTP_StatusCode status, size_t content_length, std::shared_ptr<char> content, Content_Type type);
    std::string to_string();
private:
    HTTP_StatusCode return_status;
    size_t content_length;
    std::shared_ptr<char> content_buff;
    Content_Type mime_type;
    std::string get_status_string(HTTP_StatusCode code);
    std::string get_content_string(Content_Type type);
};

#endif // HTTP_RESPONSE_H
