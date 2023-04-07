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
#include "../headers/client.hpp"
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
	getline(read_file, str);
	if(!getline(read_file, str))
	{
		cout << "config file is empty\n";
	}
	// now we should convert ifstream to string
	string the_str (istreambuf_iterator<char>(read_file),(istreambuf_iterator<char>()));
	read_file.close();
	vector<string> config_line = ft_divise(the_str, "\n");
	//exit(0);
	// vector<string>::iterator ii ;

	// for(ii = config_line.begin(); ii != config_line.end(); ii++)
	// {
	// 	std::cout << "Line by line -->" << *ii << std::endl; 
	// }
	// exit(0);
	while (count < config_line.size())
	{
		vector<string>::iterator iter1 = config_line.begin() + count;
		vector<string> world_line = ft_divise(*iter1, white_espace);
		// std::cout << "word[0] -->" << world_line[0] << endl;
		// std::cout << "word[1] -->" << world_line[1] << endl;

		// vector<string>::iterator ip ;
		// for(ip = word_line.begin(); ip != word_line.end(); ip++)
		// {
		// 	std::cout << "elem->" << *ip << endl;
		// }
		vector<string>::iterator iter2 = world_line.begin();
		if (*iter2 == "server")
		{
			server *serv = parse_server(config_line, &count);;
			for(set<server*>::iterator iter1 = servers.begin(); iter1 != servers.end() ; iter1++)
			{
				if((*iter1)->get_ip_address() == serv->get_ip_address() && (*iter1)->get_port_listen() == serv->get_port_listen())
				{
					set<string> server_names = (*iter1)->get_server_name();
					for(set<string>::iterator iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
					{
						for(set<string>::iterator iter3 = serv->get_server_name().begin(); iter3 != serv->get_server_name().end(); iter3++)
						{
							if((*iter2) == (*iter3))
							{
								std::cout << BLUE << "MyServer: [warn] conflicting server name on" << serv->get_ip_address() << ":" << serv->get_port_listen() << ", ignored" << endl;
								exit(0);
							}
						}
					}
				}
			}
			push_in_server(serv);
		}
		count++;
	}

}




void Webserver::setup(void)
{
	

	int file_descriptor;
	

	fd = 0;
	int tmp_fd;
	//Clear an fd_set
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	for (set<server*>::iterator server = servers.begin(); server != servers.end(); server++)
	{
		file_descriptor = (*server)->EstablishConnection();	
		//Add a file_descriptor to an fd_set
		FD_SET(file_descriptor, &readfds);
		if(file_descriptor > fd)
		{
			fd = file_descriptor;
		}
	}


	while(true)
	{
		for(set<Clients*>::iterator iter1= clients.begin(); iter1 != clients.end(); iter1++)
		{
				
			tmp_fd	= (*iter1)->get_file_descriptor();	
		}
		select(fd + 1, &readfds, &writefds, NULL, 0);
		for (set<server*>::iterator iter2 = servers.begin(); iter2 != servers.end(); iter2++)
		{
			if (FD_ISSET((*iter2)->get_fd_socket(), &readfds))
			{
				// new client connected
				Clients *client = new Clients((*iter2)->get_fd_socket(), servers);
				clients.insert(client);

				FD_SET(client->get_file_descriptor(), &readfds);
				FD_SET(client->get_file_descriptor(), &writefds);
			}
		}
	}

	//handle multiple socket connections with fd_set and select 
	//When writing server programs using sockets , it becomes necessary to handle multiple connections at a time , since a server needs to serve multiple clients.

}


