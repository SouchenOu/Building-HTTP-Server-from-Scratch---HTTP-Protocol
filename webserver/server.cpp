/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <fcntl.h>

server::server()
{
	client_max_body_size = 1024;
	fd_socket = 0;
}

server::~server()
{
	DEBUG("KILLING server");
	close(fd_socket);
	DEBUG("KILLED");
}

int server::EstablishConnection(void)
{
	fd_socket = socket(AF_INET, SOCK_STREAM , 0);
	if (fd_socket == -1)
	{
		perror("Error: Problem creation a socket");
		exit(1);
	}
	//Log("Listening socket created on port: " + to_string_custom(port), GREEN);

	address.sin_family = AF_INET;
	address.sin_port = htons(port_listen);
	address.sin_addr.s_addr = htonl(ip_address);
	//inet_pton(AF_INET, ip_address.c_str(), &(address.sin_addr));

	int opt = 1;
	// Need to check conn alive and stuff
	setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if (bind(fd_socket, (const struct sockaddr *)&address, sizeof(address)) == -1)
	{
		perror("Error : Problem binding");
		exit(1);
	}
	// Change max number of clients
	listen(fd_socket, SOMAXCONN);
	return (fd_socket);
}

bool	server::is_valid(string &error) const
{
	int fd;

	if (get_port_listen() == 0)
	{
		error = "port is not set";
	}
		
	if (get_root() == "")
	{
		error = "root is not set";
	}
	if (get_index() == "")
	{
		error = "index is not set";
	}
		
	if (get_client_max_body_size() == 0)
	{
		error = "max_client_body_size is not set";
	}

	if (get_ip_address() == "")
	{
		error = "ip_address is not set";
	}		
		
	
		
	map<string, string> cgis = get_cgis();

	for (map<string, string>::iterator cgi = cgis.begin(); cgi != cgis.end(); cgi++)
	{
		fd = ::open(cgi->second.c_str(), O_RDONLY);
		if (fd <= 0)
			error = "cgi " + cgi->second + " is unavailable";
		close(fd);
	}

	map<unsigned int, string> error_pages = get_error_pages();

	for (map<unsigned int, string>::iterator error_page = error_pages.begin(); error_page != error_pages.end(); error_page++)
	{
		fd = ::open((get_root() + error_page->second).c_str(), O_RDONLY);
		if (fd <= 0)
			error = "error_page " + get_root() + error_page->second + " is unavailable";
		close(fd);
	}

	list<Location> locations = get_locations();

	if (!locations.size())
		error = "location is not set";

	for (list<Location>::iterator location = locations.begin(); location != locations.end(); location++)
	{
		if (!location->is_valid(error))
			return false;
	}
	return (error.length() == 0);
}

// ************************getters

unsigned int	server::get_port_listen() const
{
	return port;
}

string			server::get_ip_address() const
{
	return ip_address;
}

list<string>	server::get_server_name() const
{
	return server_names;
}

map<unsigned int, string>	server::get_error_pages() const
{
	return error_pages;
}

string			server::get_root() const
{
	return root;
}

string			server::get_index() const
{
	return index;
}

long long		server::get_max_client_body_size() const
{
	return max_client_body_size;
}

list<Location>	server::get_locations() const
{
	return locations;
}


map<string, string>	server::get_cgis() const
{
	return cgis;
}


int server::get_fd_socket(void) const
{
	return fd_socket;
}




// ********************************setters

void	server::set_port_listen(const unsigned int port_listen)
{
	this->port_listen = port_listen;
}


void	server::set_ip_address(const string ip_address)
{
	this->ip_address = ip_address;
}


void	server::set_server_name(const list<string> server_name)
{
	this->server_name = server_name;
}

void	server::set_error_pages(const map<unsigned int, string> error_pages)
{
	this->error_pages = error_pages;
}


void	server::set_client_max_body_size(const long long client_max_body_size)
{
	this->client_max_body_size = client_max_body_size;
}


void	server::set_root(const string root)
{
	this->root = root;
}

void	server::set_index(const string index)
{
	this->index = index;
}

void	server::set_locations(const list<Location> locations)
{
	this->locations = locations;
}


void	server::set_cgis(const map<string, string> cgis)
{
	this->cgis = cgis;
}




void	server::push_in_cgi(const string extention_name, const string exec_path)
{
	this->cgis.insert(pair<string, string>(extention_name, exec_path));
}

void	server::push_in_error_page(const pair<unsigned int, string> error_page)
{
	this->error_pages.insert(error_page);
}

void	server::push_in_server_name(string server_name)
{
	this->server_names.push_back(server_name);
}

void	server::push_in_location(Location location)
{
	this->locations.push_back(location);
}