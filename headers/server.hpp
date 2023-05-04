/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef SERVER_HPP
# define SERVER_HPP


// # include <iostream>
// # include <fstream>
// # include <sstream>
// # include <string>
// # include <cstdlib>
// #include <fcntl.h>
// # include <unistd.h>
// #include "string.h"

// # include <netinet/in.h>
// # include <arpa/inet.h>
// # include <sys/select.h>
// # include <sys/socket.h> 

// # include <vector>
// #include <set>
// # include <map>
//# include "Location.hpp"
// #include "../webserver/functions_help.cpp"
#include "tools.hpp"


class Location;

class server
{
	private :
        unsigned int									port_listen; // port == listen in config_file
		std::string										ip_address;
		std::set<std::string>							server_name; //domain_name
		std::map<unsigned int, std::string>				error_pages;
		//By default, NGINX has a limit of 1MB on file uploads. If the size of a request exceeds the configured value, then the 413 Request Entity Too Large error is returned. To upload files larger than 1 MB, configure the client_max_body_size directive in the NGINX configuration files.
		long long										client_max_body_size;
		std::string										root; 
		std::string										index; 
		std::map<std::string, std::string>				cgis; 
		std::list<Location>							locations;
		



		
		// some used variable 
		int									fd_socket;
		int 								new_socket;
		std::string 						read_buffer;
		int									value;
		//With this, whenever a client tries to connect to our server, they will know what address to send their network request to.

		//the struct sockaddr holds socket address information for many types of sockets.
		struct sockaddr_in					address;

	public:
		server();
		~server();
	

	// getters
		unsigned int						get_port_listen(void) const;
		std::string							get_ip_address(void) const;
		std::set<std::string>					get_server_name(void) const;
		std::map<unsigned int, std::string>		get_error_pages(void) const;
		long long							get_client_max_body_size(void) const;
		std::string							get_root(void) const;
		std::string							get_index(void) const;
		std::list<Location>				get_locations(void) const;
		std::map<std::string, std::string>			get_cgis(void) const;
		int									get_fd_socket();
		int									get_new_socket();
		struct sockaddr* get_address(void);


		// some used functions
		int							Create_server_socket(void);
		//server* 					parse_server(vector<string> config_file, size_t *count);
		
		//settters
		
		void						set_port_listen(const unsigned int listen);
		void						set_ip_address(const std::string ip_address);
		void						set_server_name(std::set<std::string> server_names);
		void						set_error_pages(const std::map<unsigned int, std::string> error_pages);
		void						set_client_max_body_size(const long long max_client_body_size);
		void						set_root(const std::string root);
		void						set_index(const std::string index);
		void						set_locations(const std::list<Location> locations);
		void						set_cgis(const std::map<std::string, std::string> cgis);
		void						set_new_socket(int new_socket);
		

		void						insert_in_location(const Location location);
		void						insert_in_server_name(const std::string server_name);
		void						insert_in_cgi(const std::string Extention_name, const std::string execute_path);
		void						insert_in_error_page(const std::pair<unsigned int, std::string> error_page);
		
		int receive_data();
};

#endif
