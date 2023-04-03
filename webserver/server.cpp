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
	address.sin_port = htons(port_listen);
	// This is your machine is IP address
	//address.sin_addr.s_addr = htonl(ip_address);

	//convert IPv4 and IPv6 addresses from text to binary form

	inet_pton(AF_INET, ip_address.c_str(), &(address.sin_addr));

	
	if (bind(fd_socket, (const struct sockaddr *)&address, sizeof(address)) == -1)
	{
		perror("Error : Problem binding");
		exit(1);
	}
	// accept client connection requests

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


// server	*server::parse_server(vector<string> config_file, size_t *count)
// {
// 	string address_ip;
// 	string address_port;
// 	//size_t size;

// 	server *serv = new server();
// 	vector<string> world1 = ft_divise(config_file[0], white_espace);

// 	if (world1[1] != "{")
// 	{//
// 		cout << "Invalid config file\n";
// 		exit(0);
// 	}
		

// 	vector<string>::iterator iter = config_file.begin() + *count;
// 	if (iter == config_file.end())
// 	{
// 		return NULL;
// 	}
		
// 	iter++;
// 	(*count)++;
// 	while (iter != config_file.end())
// 	{
// 		vector<string> words2 = ft_divise(*iter, white_espace);
// 		if (!words2.size() || words2[0][0] == '#')
// 		{
// 			iter++;
// 			(*count)++;
// 			continue;
// 		}
// 		if (words2[0] == "}")
// 		{
// 			break;
// 		}
	
			
// 		// listen
// 		// example     listen 127.0.0.1:8080;
// 		/**listen: The IP address / port combination that this server block is 
// 		 * designed to respond to. If a request is made by a client that matches these values,
// 		 *  this block will potentially be selected to handle the connection*/
// 		else if (words2[0] == "listen")
// 		{
// 			if (words2.size() != 2)
// 			{
				
// 					std::cout << BLUE  <<  "--> server configuration is invalid: should have another argument after listen" << endl;
// 					exit(0);
// 			}
// 			vector<string> listen_words = ft_divise(words2[1], ":");
			
			

// 			if (listen_words.size() == 1)
// 			{
// 				address_ip = "0.0.0.0";
// 				address_port = listen_words[0];
// 			}
// 			else if(listen_words.size() == 2)
// 			{
// 				address_ip = listen_words[0];
// 				address_port = listen_words[1];
// 			}
				
// 			if (address_ip == "localhost")
// 			{
// 				address_ip = "127.0.0.1";
// 			}
				
// 			serv->set_ip_address(address_ip);

// 			if (is_integer(address_port) == 0)
// 			{
// 				std::cout << BLUE  << "--> server configuration is invalid: address port should be an integer" << endl;
// 				exit(0);
// 			}
// 			serv->set_port_listen(atoi(address_port.c_str()));

// 		}
// 		// server_name
// 	/******server_name: This directive is the other component used to select a server block for processing. If there are multiple server blocks with listen directives of the same specificity that can handle the request,
// 	 * 
// 	 *  Nginx will parse the “Host” header of the request and match it against this directive.*/
// 		else if (words2[0] == "server_name")
// 		{
// 			if (words2.size() < 2)
// 			{
// 				std::cout << BLUE  << "--> server configuration is invalid: should have another argument after server_name" << endl;
// 				exit(0);
// 			}
// 			for (vector<string>::iterator server_name = words2.begin() + 1; server_name != words2.end(); server_name++)
// 			{
// 				serv->push_in_server_name(*server_name);
// 			}
// 		}
		
// 		else if (words2[0] == "error_page")
// 		{
// 			if (words2.size() != 3)
// 			{
// 				std::cout << BLUE  << "--> server configuration is invalid: should have three argument after error_page" << endl;
// 				exit(0);
// 			}
// 			//The C++ pair allows you to store two disparate items as a single entity.
// 			serv->push_in_error_page(pair<unsigned int, string>((unsigned int)atoi(words2[1].c_str()), words2[2]));
// 		}
// 		// the index directive defines the index file is name (The default value is index.html)
// 		else if (words2[0] == "index")
// 		{
// 			if (words2.size() != 2)
// 			{
// 				std::cout << BLUE  <<  "--> server configuration is invalid: should have another argument after index" << endl;
		
// 				exit(0);
// 			}
// 			serv->set_index(words2[1]);
// 		}
// 		//we will increase the size limit of the file limit in Nginx to any size you want by using 
// 		// client_max_body_size
// 		else if (words2[0] == "client_max_body_size")
// 		{
// 			if (words2.size() != 2)
// 			{
// 				std::cout << BLUE  <<  "--> server configuration is invalid: should have another argument after client_max_body_size" << endl;
// 				exit(0);
// 			}
// 			if (!is_integer(words2[1]))
// 			{
// 				std::cout << BLUE  <<  "--> server configuration is invalid: should have a number after client_max_body_size" << endl;
	
// 				exit(0);
// 			}
// 			serv->set_client_max_body_size(atoi(words2[1].c_str()));
// 		}
// 		/******Nginx fastcgi is used to translate requests of clients from an application server which was not handled the request of the client directly.*/
// 		/****We can say that the nginx fastcgi protocol means improving the performance by running each request in a process that was separate in nginx.*/

// 		//CGI was the earliest common method available that allowed a web page to be interactive
// 		else if (words2[0] == "cgi")
// 		{
// 			if (words2.size() != 3)
// 			{
// 				std::cout << BLUE  << "--> server configuration is invalid: should have three argument after cgi" << endl;
// 				exit(0);
// 			}
// 			serv->push_in_cgi(words2[1], words2[2]);
		
// 		}
		
// 		else if (words2[0] == "root")
// 		{
// 			if (words2.size() != 2)
// 			{
// 				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after root" << endl;

// 				exit(0);
// 			}
// 			string root_tmp = words2[1];
// 			if (root_tmp.size() > 0 && root_tmp[0] == '/')
// 				root_tmp = root_tmp.substr(1);
// 			if (root_tmp.size() > 1 && root_tmp[root_tmp.size() - 1] == '/')
// 				root_tmp.resize(root_tmp.size() - 1);
// 			serv->set_root(root_tmp);
// 		}

// 		/***** each location is used to handle a certain type of client request,
// 		 *  and each location is selected by matching the location definition against the client request through a selection algorithm.*/


// 		/*****NGINX’s location setting helps you set up the way in which NGINX responds to requests for resources inside the server.*/

// 		//One or more location contexts in a server context define how to process specific sets of URIs.
// 		else if (words2[0] == "location")
// 		{
// 			Location location;
// 			if (words2.size() != 3)
// 			{
// 				std::cout << BLUE  <<  "--> server configuration is invalid: should have another argument after location" << endl;

// 				exit(0);
// 			}
// 			size_t old_count = *count;

// 			// we shouls parse location
		
// 			string path;
// 			path = words2[1];
		
// 			if(path.size() > 1 && path[path.size() - 1] == '/')
// 			{
// 				path.resize(path.size() - 1);
// 			} 
// 			if(words2[2] != "{")
// 			{
// 				std::cout << BLUE  <<  "--> should have open bracket after location and path" << endl;
// 				exit(0);
// 			}

// 			(*count)++;
// 			// first line after location line
// 			vector<string>::iterator iter2 = config_file.begin() + *count;
// 			while(iter2 != config_file.end())
// 			{
// 				vector<string> line = ft_divise(*iter, white_espace);
// 				if(line.size() == 0 || line[0][0] == '#')
// 				{
// 					iter2++;
// 					(*count)++;
// 					continue;
// 				}
// 				if(line[0] ==  "}")
// 				{
// 					break ;
// 				}
// 				// root in location
// 				if(line[0] == "root")
// 				{
// 					if(line.size() == 0)
// 					{
// 						std::cout << BLUE  << "--> should have another argument after root" << endl;
// 						exit(0);
// 					}

// 					if(line[1].size() > 0 && line[1][line[1].size() - 1] == '/')
// 					{
// 						line[1].resize(line[1].size() - 1);
// 					}
// 					location.set_root(line[1]);
// 				}
// 				// try_files in location 
// 				else if(line[0] == "try_files")
// 				{
// 					if(line.size() < 2)
// 					{
// 						std::cout << BLUE  << "--> should have minimum one argument after try_files argument" << endl;
// 						exit(0);
// 					}
// 					if(line[1].size() > 0 && line[1][line[1].size() - 1] == '/')
// 					{
// 						line[1].resize(line[1].size() - 1);
// 					}
// 					location.set_try_files(line[1]);
// 				}
// 				// alias in location 

// 				else if(line[0] == "alias")
// 				{
// 					if(line.size() != 2)
// 					{
// 						std::cout << BLUE  << "--> should have another argument after alias" << endl;
// 						exit(0);
// 					}
// 					if(line[1].size() > 0 && line[1][line[1].size() - 1] == '/')
// 					{
// 						line[1].resize(line[1].size() - 1);
// 					}
// 					location.set_alias(line[1]);
// 				}

// 				// return in location
// 				else if(line[0] == "return")
// 				{
// 					if(line.size() != 3)
// 					{
// 						std::cout << BLUE  << "--> should have two argument after return" << endl;
// 						exit(0);
// 					}
// 					if(line[2].size() > 0 && line[2][line[2].size() - 1] == '/')
// 					{
// 						line[2].resize(line[2].size() - 1);
// 					}
// 					int number = atoi(line[1].c_str());

// 					if(number == 301 || number == 302  || number == 303 || number == 307 || number == 308 )
// 					{
// 						std::cout << BLUE  <<  "--> invalid number" << endl;
// 						exit(0);
// 					}
// 					location.set_http_redirection(number);	
// 					location.set_return_line(line[2]);
					
// 				}
// 				// autoindex
// 				else if(line[0] == "autoindex")
// 				{
// 					if(line.size() != 2)
// 					{
// 						std::cout << "should have another argument after autoindex" << endl;
// 						exit(0);
// 					}

// 					location.set_autoindex(line[1]);
					
// 				}
// 				else if (line[0] == "index")
// 				{
// 					if(line.size() != 2)
// 					{
// 						std::cout << "should have another argument after index" << endl;
// 						exit(0);
// 					}
// 					location.set_index(line[1]);
// 				}
// 				else 

// 					std::cout << "It is another location \n ";



// 			}

			



// 			serv->push_in_location(location);
// 			iter = iter +  *count - old_count;
// 		}
		
		
	
// 		iter++;
// 		(*count)++;
// 	}
// 	// vector<string> end_file = ft_divise(*iter, white_espace);
// 	// while (!end_file.size() || end_file[0] != "}")
// 	// {
// 	// 	(*count)++;
// 	// 	end_file = ft_divise(config_file[*count], white_espace);
// 	// }
// 	// if (end_file.size() && end_file[0] != "}")
// 	// {
// 	// 	std::cout << BLUE  << serv.get_root() << "--> server configuration is invalid: missig close bracket" << endl;
// 	// 	exit(0);
// 	// }
	
// 	return serv;
// }





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