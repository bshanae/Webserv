#include "VirtualServerParametrsBuolder.hpp"
#include <cctype>
#include "tools/exceptions/FileException.hpp"
bool is_all_digit(std::string str,std::string::iterator i)
{
    for(;  i + 1 != str.end() ; i++ ){
        if (*i =='\0')
            return true;
        if (std::isdigit(*i) != true)
            return false;
    }
    return true;
}
void VirtualServerParametrsBuolder::parse_string(std::string &str){
    size_t i = str.find_first_of(' ');
    std::string param;
    if (i == std::string::npos )
        param = "";
    else
        param = str.substr(i);
    std::string name = str.substr(0,i);
    
    size_t trimmed_end = param.find_first_not_of(" ");
    if (trimmed_end != std::string::npos)
        param.erase(0,trimmed_end);
    
    if (temp_location.hasValue() &&  name == "uri")
        temp_location->parse_url(param);
    else if(temp_location.hasValue() &&  name ==  "path")
        temp_location->parse_path(param);
    else if(temp_location.hasValue() && name ==  "redirect")
        temp_location->parse_redirect(param);
    else if(temp_location.hasValue() && name ==  "limit_except")
        temp_location->parse_limits(param);
    else if(temp_location.hasValue() && name ==  "}")
    {
        for (std::vector<location>::iterator i = locations.begin(); i != locations.end(); i++)
        {
            if (temp_location->uri == i->uri)
                throw FileException("locatoin already exist");
        }
        this->locations.push_back(temp_location.getValue());
        temp_location.reset();
    }
    else if (name == "listen")
        this->parse_port_and_ip(param);
    else if (name == "server_name")
        this->parse_name(param);
    else if (name == "root")
        this->parse_root(param);
    else if (name == "index")
        this->parse_index(param);
    else if (name == "error_page")
        this->parse_err_page(param);
    else if (name == "client_max_body_size")
        this->parse_max_body_size(param);
    else if (name == "upload")
        this->parse_upload(param);
    else if (name == "cgi_path")
        this->parse_upload(param);
    else if (name == "location" && param == "{")
        temp_location = location();
    else 
        throw FileException("unknown word");

}
std::string::iterator VirtualServerParametrsBuolder::parse_init_ip(std::string str){
    std::string::iterator i = str.begin();
    if (std::atoi(str.c_str()) > 256)
        throw FileException("wrong ip");
    for(int j = 0 ; j  < 3 ; j++){
        if (std::atoi(str.c_str() + (i - str.begin())) > 256)
            throw FileException("wrong ip");
        while(*i != '.' && *i != ':')
            i++;
        if (*i != '.')
             throw FileException("wrong ip");
        i++;
    }
     if (std::atoi(str.c_str() + (i - str.begin())) > 256)
             throw FileException("wrong ip");
    while(*i != '.' && *i != ':')
            i++;
    if (*i != ':')
         throw FileException("wrong ip");
    
    this->ip_adress = str.substr(0, i - str.begin());
    i++;
    return i;
    
}
VirtualServerParametrsBuolder::VirtualServerParametrsBuolder():
    port(1080),
    name(""),
    root("/"),
    index("index.html"),
    error_page("404.html"),
    client_max_body_size(0),
    upload("/upload"),
    cgi_path("/cgi"),
    locations(),
    ip_adress("0.0.0.0")
{}

void VirtualServerParametrsBuolder::parse_port_and_ip(std::string& str){
    std::string::iterator i = str.begin();
    if (str.find(":") == std::string::npos){
        this->ip_adress = "0.0.0.0";
    }
    else{
        i = this->parse_init_ip(str);    
    }
    if (is_all_digit(str,i) == false )
            throw FileException("wrong port number");
    int temp_port = std::atoi(str.c_str() + (i - str.begin()));
    if (temp_port <= 0 && temp_port > 65535 )
        throw FileException("wrong port number");
    this->port = temp_port;

}
void VirtualServerParametrsBuolder::parse_root(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong root");
    this->root = str;
}
void VirtualServerParametrsBuolder::parse_index(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong index");
    this->index = str;
}
void VirtualServerParametrsBuolder::parse_err_page(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong err_page");
    this->error_page = str;
}
void VirtualServerParametrsBuolder::parse_max_body_size(std::string& str)
{
    if (is_all_digit(str,str.begin()) == false)
        throw FileException( "wrong max body size");
    this->client_max_body_size = std::atoll(str.c_str());
}
void VirtualServerParametrsBuolder::parse_upload(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException( "wrong upload");
    this->upload = str;
}
void VirtualServerParametrsBuolder::parse_cgi_path(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException( "wrong cgi_path");
    this->cgi_path = str;
}
void VirtualServerParametrsBuolder::parse_name(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException( "wrong name");
    
    this->name = str;
}