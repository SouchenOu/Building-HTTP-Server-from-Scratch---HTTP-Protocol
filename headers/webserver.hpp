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
# include <sys/stat.h> // mkdir
# include <dirent.h> // dirent readdir
# include <sys/types.h>
# include <sys/wait.h>

//* NETWORK INCLUDES
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/socket.h> // bind

# include <list>
# include <map>


# include "client.hpp"
# include "server.hpp"

class Webserver
{
	private:
		list<server*>	servers;
	

	public:
    // constructer
		Webserver(const string config_file);
    // Destructer
		~Webserver();

		
		void	build(void);
		void	push_in_server(server *serv);
};

#endif
