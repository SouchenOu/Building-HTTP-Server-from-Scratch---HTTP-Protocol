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
//#include "parce_config_file.cpp"
#include "../headers/server.hpp"
# define white_espace "; \t"


Webserver::Webserver()
{
	std::cout << "Welcome this is my server\n";
}

Webserver::~Webserver()
{
	
}

void	Webserver::push_in_server(server *serv)
{
	servers.insert(serv);
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
	
	while (count < config_line.size())
	{
		vector<string>::iterator iter1 = config_line.begin() + count;
		vector<string> word_line = ft_divise(*iter1, white_espace);

		vector<string>::iterator iter2 = word_line.begin();
		if (*iter2 == "server")
		{
			server *serv = parse_server(config_line, &count);
			// for (set<server*>::const_iterator sserver = servers.begin(); sserver != servers.end(); sserver++)
			// {
			// 	if ((*sserver)->get_ip_address() == serv->get_ip_address() && (*sserver)->get_port_listen() == serv->get_port_listen())
			// 	{
			// 		if ((*sserver)->get_server_name().size() == 0 || serv->get_server_name().size() == 0)
			// 		{
			// 			std::cout << BLUE  <<  "[warn] conflicting server name "" on " << serv->get_ip_address() << ":" << serv->get_port_listen()<< ", ignored" << endl;
			// 			delete serv;
			// 			exit(0);
			// 		}
						
			// 	}
			// }
			push_in_server(serv);
		}
		count++;
	}

}



void Webserver::setup(void)
{
	
	//FD_ZERO(&listen_set);
	//FD_ZERO(&write_set);
	int file_descriptor;
	for (set<server*>::iterator server = servers.begin(); server != servers.end(); server++)
	{
		 file_descriptor = (*server)->EstablishConnection();
		//FD_SET(fd, &listen_set);
		//if (fd > high_fd)
		//	high_fd = fd;
	}
}


