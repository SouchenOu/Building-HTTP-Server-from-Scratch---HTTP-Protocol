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

#include "../headers/server.hpp"
#include <fcntl.h>
#include "sys/socket.h"
#include "netinet/in.h"

server::server()
{
	client_max_body_size = 1024;
	fd_socket = 0;
}

server::~server()
{
	close(fd_socket);
	
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


// ************************getters

unsigned int	server::get_port_listen() const
{
	return port_listen;
}

string			server::get_ip_address() const
{
	return ip_address;
}

set<string>	server::get_server_name() const
{
	return server_name;
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

long long		server::get_client_max_body_size() const
{
	return client_max_body_size;
}

vector<Location>	server::get_locations() const
{
	return locations;
}


map<string, string>	server::get_cgis() const
{
	return cgis;
}


int server::get_fd_socket(void)
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


void	server::set_server_name(set<string> server_name)
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

void	server::set_locations(const vector<Location> locations)
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
	this->server_name.insert(server_name);
}

void	server::push_in_location(Location location)
{
	this->locations.push_back(location);
}