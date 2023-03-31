/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserver.hpp"
#include "../headers/server.hpp"
#include "Parcing.cpp"
# define isspace "; \t"
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include "functions_help.cpp"
#include "cstring"
#include "string"

Webserver::Webserver()
{
}

Webserver::~Webserver()
{
	
}

void	Webserver::push_in_server(server *serv)
{
	servers.push_back(serv);
}


void Webserver::parcing_config_file(const string config_file)
{

	size_t count = 0;
	//Ifstream c++ is a file input stream that allows us to read any information contained in the file
    std::ifstream read_file(config_file);
	string str;
	if(!getline(read_file, str))
	{
		cout << "config file is empty\n";
	}
	// now we should convert ifstream to string
	string the_str (istreambuf_iterator<char>(read_file),(istreambuf_iterator<char>()));

	read_file.close();
	vector<string> config_line = ft_divise(the_str, "\n");
	vector<string>::iterator iter1 = config_line.begin();
	
	while (count < config_line.size())
	{
		vector<string>::iterator iter1 = config_line.begin() + count;
		vector<string> word_line = ft_divise(*iter1, isspace);

		vector<string>::iterator iter2 = word_line.begin();
		if (*iter2 == "server")
		{
			server *serv = parse_server(config_line, &count);
			// for (list<server*>::const_iterator sserver = servers.begin(); sserver != servers.end(); sserver++)
			// {
			// 	if ((*sserver)->get_ip_address() == serv->get_ip_address() && (*sserver)->get_port_listen() == serv->get_port_listen())
			// 	{
			// 		if ((*sserver)->get_server_name().size() == 0 || serv->get_server_name().size() == 0)
			// 		{
			// 			std::cout << BLUE  <<  "[warn] conflicting server name "" on " << serv->get_ip_address() << ":" << serv->get_port_listen()<< ", ignored" << endl;
			// 			delete serv;
			// 			exit(0);
			// 		}
						
			// 		for (list<string>::iterator server_names = server_name.begin(); server_names != server_name.end(); server_names++)
			// 		{
			// 			for (list<string>::iterator new_server_name = serv->get_server_name().begin(); new_server_name != serv->get_server_name().end(); new_server_name++)
			// 			{
			// 				if (*server_name == *new_server_name)
			// 				{
			// 					std::cout << BLUE  <<  "[warn] conflicting server name "" on " << serv->get_ip_address() << ":" << serv->get_port_listen()<< ", ignored" << endl;
			// 					delete serv;
			// 					exit(0);
			// 				}
			// 			}
			// 		}
			// 	}
			// }
			push_in_server(serv);
		}
		count++;
	}

}

//The select() function indicates which of the specified file descriptors is ready for reading, ready for writing, or has an error condition pending


void Webserver::setup(void)
{
	
}



