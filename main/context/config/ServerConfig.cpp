#include "ServerConfig.h"
#include "VirtualServerParametrs.hpp"
#include "VirtualServerParametrsBuolder.hpp"
#include <string>
#include <iostream>
#include "tools/exceptions/FileException.hpp"
#include <fstream>
void Trim(std::string& out_line);

VirtualServerParametrsBuolder ServerConfig::parse_server(std::ifstream &file)
{
    std::string str;
    VirtualServerParametrsBuolder server;
    while(true ){
        getline(file,str);
        Trim(str);
        if(str.size() == 0)
            continue;
        if ( str == "}" && ! server.temp_location.hasValue())
            return server;
        server.parse_string(str);
    }
    return server;
}
ServerConfig::ServerConfig(const char * file_name)
{
   std::ifstream file(file_name);
    
	if (!file.is_open()){
		throw FileException("cant open file");
    }
    std::string str;
    while( ! file.eof())
    {
        getline(file,str);
        Trim(str);
        if (str.size() == 0)
            continue;
        else if ( str == "server {")
            this->add_server(parse_server(file));
        else
            throw FileException("Unknown simbole");
    } 

}



void ServerConfig::add_server( VirtualServerParametrsBuolder serv){

    VirtualServerParametrs temp = VirtualServerParametrs(serv);
    for(std::vector<VirtualServerParametrs>:: iterator i = servers.begin();i != servers.end(); i++)
    {
        if (serv.port == i->port && serv.name == i->name)
        {
            throw FileException("Same server already exist");
        }
    }
    servers.push_back(temp);
}
const std::vector< VirtualServerParametrs>& ServerConfig::get_servers() const {
    return servers;
}

void ServerConfig::print_par(){
    for (std::vector<VirtualServerParametrs>::iterator i = servers.begin(); i != servers.end();i++)
    {
        std::cout << "server {\n" 
        << "name " << i->name 
        << "\nport " << i->port
        << "\nip " << i->ip_adress
        << "\nroot " << i->root
        << "\nerror_page " << i->error_page
        << "\nClient_max_body_size " << i->client_max_body_size
        << "\nupload " << i->upload
        << "\ncgi_path " << i->cgi_path;
        for ( std::vector<location>::const_iterator j = i->locations.begin() ; j != i->locations.end() ; j++ )
        {
            std::cout << " location {\n" 
            << " uri " << j->uri 
            << "\n path " << j->path
            << "\n redirect " << j->redirect
            << "\n limit_except " <<  int (j->limit_except)
            << " \n }\n";
        }
        std::cout << "}\n";
    }

}