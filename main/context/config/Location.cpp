#include "Location.hpp"
#include <cctype>
#include "tools/exceptions/FileException.hpp"


location::location():
        uri(""),
        path("/"),
        redirect(""),
        limit_except(GET & POST & DELETE)
{}
void location::parse_url(std::string &str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong url");
    this->uri = str;
}
void location::parse_path(std::string &str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong path");
    this->path = str;
}
void location::parse_redirect(std::string &str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong redirection");
    this->redirect = str;
}
void location::parse_limits(std::string &str)
{
    this->limit_except = 0;
        while (str.size() != 0 )
        {
            size_t trim = str.find_first_of(",");
            std::string temp = str.substr(0,trim);
            if (trim != std::string::npos)
                str.erase(0,trim + 1);
            else 
                str.erase(0,trim);
            if (temp == "")
                return;
            else if (temp == "GET")
                this->limit_except = this->limit_except | GET;
            else if (temp == "POST")
                this->limit_except = this->limit_except | POST;
            else if (temp == "DELITE")
                this->limit_except = this->limit_except | DELETE;
            else
                throw FileException("wrong limits");
        }
};

