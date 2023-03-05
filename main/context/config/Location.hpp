#pragma once
#include <string>
enum  methods{ GET = 1, POST = 2,DELETE = 4};
class location{
    public:
        std::string uri;
        std::string path;
        std::string redirect;
        char limit_except;
        location();
        void parse_url(std::string &str);
        void parse_path(std::string &str);
        void parse_redirect(std::string &str);
        void parse_limits(std::string &str);
};
