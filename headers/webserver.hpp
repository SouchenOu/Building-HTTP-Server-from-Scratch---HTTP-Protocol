/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:40:39 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 09:40:41 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP



#include "headers.hpp" 

//# include "server.hpp"

class server;

class Webserver
{
	private:
	/**You can declare multiple server contexts, 
	 * because each instance defines a specific virtual server to handle client 
	 * requests. You can have as many server blocks as you need, each of which can handle 
	 * a specific subset of connections.*/
		std::set<server*>	servers;
		fd_set      set_fd;
	

	public:
    // constructer
		//Webserver(const string config_file);
		Webserver();
    // Destructer
		~Webserver();

		void parcing_config_file(const std::string config_file);
		void	setup(void);
		void	push_in_server(server *serv);
		bool conflict_ip_address(const string &new_ip_address, const unsigned int new_port, const set<string> &new_server_names);
};

#endif
