#pragma once



#include "VirtualServerParametrs.hpp"
#include "VirtualServerParametrsBuolder.hpp"
#include <vector>
#include <map>
class ServerConfig
{
    public:
        ServerConfig(const char *str);
        typedef  std::vector<VirtualServerParametrs>::iterator iterator;
	    void add_server( VirtualServerParametrsBuolder serv);
	    const std::vector<VirtualServerParametrs>& get_servers() const;
        void print_par();

    private:
        VirtualServerParametrsBuolder parse_server(std::ifstream &file);
        ServerConfig& operator=(const ServerConfig& that);
        ServerConfig(const ServerConfig& that);

	    std::vector<VirtualServerParametrs> servers;
};
