#include <memory>
#include <sstream>

#include "http_response.h"

HTTP_Response::HTTP_Response(HTTP_StatusCode status) : return_status(status)
{
}

HTTP_Response::HTTP_Response(HTTP_StatusCode status,
                             size_t _content_length,
                             std::shared_ptr<char> content,
                             Content_Type type) :
    content_length(_content_length),
    content_buff(content),
    mime_type(type),
    return_status(status)
{
}

std::string HTTP_Response::to_string()
{
    std::stringstream builder;

    std::string status_string = get_status_string(return_status);

    builder << HTTP_VERSION << " " << return_status << " " << status_string << '\n';

    if (content_buff) {
        builder << "Content-Type: " << get_content_string(mime_type) << '\n';
        builder << "Content-Length: " << content_length << '\n';
        builder << '\n';
        builder << content_buff.get();
    }
    return builder.str();
}

std::string HTTP_Response::get_status_string(HTTP_StatusCode code) {
    switch (code) {
    case NOT_FOUND_404:
        return "Not Found";
    case OK_200:
        return "OK";
    case BAD_REQUEST_400:
        return "Bad Request";
    }
    return "Not Implemented";
}

std::string HTTP_Response::get_content_string(Content_Type type) {
    switch (type) {
    case TEXT_HTML:
        return "text/html";
    }
    return "Not Implemented";
}
