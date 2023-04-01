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



#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
# include <ctime>
# include <sys/stat.h> 
# include <dirent.h> 
# include <sys/types.h>
# include <sys/wait.h>


# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/socket.h> 

# include <set>
# include <map>


# include "client.hpp"
# include "server.hpp"

class Webserver
{
	private:
	/**You can declare multiple server contexts, 
	 * because each instance defines a specific virtual server to handle client 
	 * requests. You can have as many server blocks as you need, each of which can handle 
	 * a specific subset of connections.*/
		set<server*>	servers;
	

	public:
    // constructer
		//Webserver(const string config_file);
		Webserver();
    // Destructer
		~Webserver();

		void parcing_config_file(const string config_file);
		void	setup(void);
		void	push_in_server(server *serv);
};

#endif
