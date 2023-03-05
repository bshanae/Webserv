#pragma once
#include <string>
#include <vector>
#include "Location.hpp"
#include "tools/templates/Optional.h"
class VirtualServerParametrsBuolder{
    private:
    std::string::iterator parse_init_ip(std::string str);
        // VirtualServer& operator= (VirtualServer &oth){};
        // VirtualServer(VirtualServer &oth){};
    public:
        int port;
        std::string name;
        std::string root;
        std::string index;
        std::string error_page;
        size_t client_max_body_size;
        std::string upload;
        std::string cgi_path;
        std::vector<location> locations;
        std::string ip_adress;
        Optional<location> temp_location;
    public:
        VirtualServerParametrsBuolder();
        void parse_string(std::string &str);
        void parse_port_and_ip(std::string& );
        void parse_name(std::string& );
        void parse_root(std::string& );
        void parse_index(std::string& );
        void parse_err_page(std::string& );
        void parse_max_body_size(std::string& );
        void parse_upload(std::string& );
        void parse_cgi_path(std::string& );

};

