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
#define BLUE    "\033[34m"
# define white_espace "; \t"


server::server()
{
	client_max_body_size = 1024;
	fd_socket = 0;
}

server::~server()
{
	//When our Server gets cleaned up (the destructor function, ~server() , is called) we want to make sure we also close the socket we’ve created for our server. 
	close(fd_socket);
	
}

int server::EstablishConnection(void)
{
	//first arg (domain or address family): For communicating between processes on different hosts connected by IPV4, we use AF_INET (IP) and AF_INET6 for processes connected by IPV6.

	/*	second arg (type) : SOCK_STREAM: TCP(reliable, connection oriented)
		SOCK_DGRAM: UDP(unreliable, connectionless)*/

	/**Third arg: (protocol)  Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.*/


	/****For TCP/IP sockets, we want to specify the IP address family ( AF_INET ) and virtual
		circuit service ( SOCK_STREAM ). Since there’s only one form of virtual circuit service, there
		are no variations of the protocol, so the last argument, protocol, is zero. Our code for
		creating a TCP socket looks like this:*/

//Creating a TCP/IP socket
	fd_socket = socket(AF_INET, SOCK_STREAM , 0);
	if (fd_socket == -1)
	{
		perror("Error: Problem creation a socket");
		exit(1);
	}
	//Before calling bind, we need to fill out this structure. The three key parts we need to set are:

	//The address family or a domain we used when we set up the socket. In our case, it’s AF_INET .
	address.sin_family = AF_INET;
	// transport address or a port number
	//The htons function can be used to convert an IP port number in host byte order to the IP port number in network byte order.
	//We will need to call htons() to ensure that the port is stored in network byte order.
	address.sin_port = htons(port_listen);
	// This is your machine is IP address
	//convert the IP address from a char * to an unsigned long and have it stored in network byte order.
	address.sin_addr.s_addr = inet_addr(ip_address.c_str());

	//convert IPv4 and IPv6 addresses from text to binary form
	//inet_pton(AF_INET, ip_address.c_str(), &(address.sin_addr));

	// int test = 1;
	// setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, &test, sizeof(test));


	//By binding the socket to a port, you are telling the operating system that this socket should be used to listen for incoming requests on that port.
	if (bind(fd_socket, (const struct sockaddr *)&address, sizeof(address)) == -1)
	{
		
		perror("Error : Problem binding");
		exit(1);
	}

	// listen for incoming requests......

	//Start Listening for Requests...
	//listen(fd_socket, backlog)
	//The backlog is the maximum number of connections that can be waiting to be accepted.

	/****marks the socket referred to by fd_socket as a passive
       socket, that is, as a socket that will be used to accept incoming
       connection requests using accept().*/

	//SOMAXCONN : Use the SOMAXCONN statement to specify the maximum number of connection requests queued for any listening socket.cle
	if(listen(fd_socket, SOMAXCONN) == -1)
	{
		perror("Error: Problem in listening\n");
	}
	return (fd_socket);
}





// ************************getters

unsigned int	server::get_port_listen() const
{
	return port_listen;
}

std::string			server::get_ip_address() const
{
	return ip_address;
}

std::set<std::string>	server::get_server_name() const
{
	return server_name;
}

std::map<unsigned int, std::string>	server::get_error_pages() const
{
	return error_pages;
}

std::string			server::get_root() const
{
	return root;
}

std::string			server::get_index() const
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


std::map<std::string, std::string>	server::get_cgis() const
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


void	server::set_ip_address(const std::string ip_address)
{
	this->ip_address = ip_address;
}


void	server::set_server_name(std::set<std::string> server_name)
{
	this->server_name = server_name;
}

void	server::set_error_pages(const std::map<unsigned int, std::string> error_pages)
{
	this->error_pages = error_pages;
}


void	server::set_client_max_body_size(const long long client_max_body_size)
{
	this->client_max_body_size = client_max_body_size;
}


void	server::set_root(const std::string root)
{
	this->root = root;
}

void	server::set_index(const std::string index)
{
	this->index = index;
}

void	server::set_locations(const vector<Location> locations)
{
	this->locations = locations;
}


void	server::set_cgis(const std::map<std::string, std::string> cgis)
{
	this->cgis = cgis;
}




void	server::push_in_cgi(const std::string extention_name, const std::string exec_path)
{
	this->cgis.insert(std::pair<std::string, std::string>(extention_name, exec_path));
}

void	server::push_in_error_page(const std::pair<unsigned int, std::string> error_page)
{
	this->error_pages.insert(error_page);
	// std::map<unsigned int, string>::iterator i;
	// i = error_pages.begin();
	// std::cout << "error_page :" << i->first << endl;
	// std::cout << "error_page :" << i->second << endl;
}

void	server::push_in_server_name(std::string server_name)
{
	this->server_name.insert(server_name);
}

void	server::push_in_location(Location location)
{
	this->locations.push_back(location);
}