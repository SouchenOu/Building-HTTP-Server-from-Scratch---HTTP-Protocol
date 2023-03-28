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


# ifndef CONFIG_HPP
# define CONFIG_HPP


# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include "string.h"

# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/socket.h> 

# include <list>
# include <map>
# include "request.hpp"
# include "Location.hpp"


using namespace std;



class server
{
	private :
		// * PARSED FROM CONFIG FILE *
        unsigned int				port_listen; // port to listen and send on ("listen" in config file)
		string						ip_address;
		list<string>				server_name; // "Host" header in HTTP request (domain names)
		map<unsigned int, string>	error_pages;
		long long					client_max_body_size;
		string						root; // directory where the webste is
		string						index; // file served when "/" is requested
		//list<Location>				locations;
		map<string, string>			cgis; // CGI's extentions names and exec paths
		
		// some used variable 
		int							fd_socket;
		struct sockaddr_in			address;

	public:
		server();
		~server();
	

	// getters
		unsigned int				get_port_listen(void) const;
		string						get_ip_address(void) const;
		list<string>				get_server_name(void) const;
		map<unsigned int, string>	get_error_pages(void) const;
		long long					get_client_max_body_size(void) const;
		string						get_root(void) const;
		string						get_index(void) const;
		list<Location>				get_locations(void) const;
		map<string, string>			get_cgis(void) const;
		int							get_fd_socket();

		// some used functions
		void						s_listen(void);
		int							EstablishConnection(void);
		bool						is_valid(string &error) const;
		
		//settters
		
		void						set_port_listen(const unsigned int listen);
		void						set_ip_address(const string ip_address);
		void						set_server_name(const list<string> server_names);
		void						set_error_pages(const map<unsigned int, string> error_pages);
		void						set_client_max_body_size(const long long max_client_body_size);
		void						set_root(const string root);
		void						set_index(const string index);
		void						set_locations(const list<Location> locations);
		void						set_cgis(const map<string, string> cgis);
		
		

		void						push_in_location(const Location location);
		void						push_in_server_name(const string server_name);
		void						push_in_cgi(const string extention_name, const string exec_path);
		void						push_in_error_page(const pair<unsigned int, string> error_page);
		
		
};

#endif
