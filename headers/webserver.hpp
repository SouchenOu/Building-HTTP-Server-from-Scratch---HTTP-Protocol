/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:40:39 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 09:40:41 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP



#include "tools.hpp" 

//# include "server.hpp"

class server;

class Webserver
{
	private:
	/**You can declare multiple server contexts, 
	 * because each instance defines a specific virtual server to handle client 
	 * requests. You can have as many server blocks as you need, each of which can handle 
	 * a specific subset of connections.*/
		std::set<server*>		servers;
		std::list<WebBrowsers*>   Browsers;
		int 				fd_max;
		fd_set				readfds;
		fd_set				writefds;
		fd_set				r_fds;
		fd_set				w_fds;
		int					activity;
		int 				value;
	
	

	public:
    // constructer
		Webserver();
    // Destructer
		~Webserver();

		void parcing_config_file(std::string config_file);
		void	Establish_connection(void);
		void	push_in_server(server *serv);
		void stop();
		void accept_connection();

		// getters
		int get_value();
		
};

#endif
