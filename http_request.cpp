#include <sstream>
#include <fstream>
#include <memory>

#include "http_request.h"
#include "httpserver.h"

HTTP_Request::HTTP_Request(const char *buff)
{   
    std::string str(buff);
    std::string tmp;
    std::stringstream ss(str);
    std::vector<std::string> tokens;

    while (ss >> tmp) {
        tokens.push_back(tmp);
    }
    if (tokens.size() < 3) {
        flags |= BAD_REQUEST;
        return;
    }
    try {
        method = parse_method(tokens);
        uri = parse_uri(tokens);
        //for now wee dont need this
        //args = parse_args(tokens);
        HTTP_version = parse_version(tokens);
    } catch (BadRequestException & e) {
        flags |= BAD_REQUEST;
        return;
    }
}

HTTP_Response HTTP_Request::do_request()
{
    size_t content_length = 0;
    if (flags & BAD_REQUEST) {
        return HTTP_Response(HTTP_StatusCode::BAD_REQUEST_400);
    } else {
        std::fstream html_file;

        html_file.open(uri, std::ios_base::in);

        if (html_file.is_open()) {
            std::streampos begin, end;
            begin = html_file.tellg();
            html_file.seekg (0, std::ios::end);
            end = html_file.tellg();
            html_file.seekg(0);

            content_length = end - begin;
            std::shared_ptr<char> buff(new char[content_length]);
            html_file.read(buff.get(), content_length);
            return HTTP_Response(HTTP_StatusCode::OK_200, content_length, buff, Content_Type::TEXT_HTML);
        } else {
            return HTTP_Response(HTTP_StatusCode::NOT_FOUND_404);
        }
    }
}

HTTP_Request::HTTP_Method HTTP_Request::parse_method(const std::vector<std::string> &tokens)
{
    std::string method = tokens[0];
    if (method == "GET") {
        return HTTP_Method::GET;
    } else {
        throw BadRequestException("Not implemented yet");
    }
}

std::string HTTP_Request::parse_uri(const std::vector<std::string> &tokens)
{
    std::string raw_uri = tokens[URI_POS];
    size_t args_pos = 0;
    if (raw_uri == "/") {
        return HTTP::HttpServer::get_instance()->config.dir + "/index.html";
    } else if ((args_pos = raw_uri.find('?')) == std::string::npos ) {
        return HTTP::HttpServer::get_instance()->config.dir + raw_uri;
    } else {
        return HTTP::HttpServer::get_instance()->config.dir + raw_uri.substr(0, args_pos);
    }
}

std::string HTTP_Request::parse_version(const std::vector<std::string> &tokens)
{
    std::string version = tokens[PROTO_POS];
    if (version != "HTTP/1.0") {
        throw BadRequestException("Not supported version");
    }
    return version;
}


BadRequestException::BadRequestException(const char *what_arg) : std::logic_error(what_arg)
{
}

BadRequestException::BadRequestException(const std::string &what_arg) : std::logic_error(what_arg)
{
}
