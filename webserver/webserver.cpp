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
#include "../headers/WebBrowser.hpp"
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
	
	int fd_socket;
	
	fd_max = 0;
	int fd;
	//Clear an fd_set
	FD_ZERO(&readfds); 
	FD_ZERO(&writefds);
	for (set<server*>::iterator server = servers.begin(); server != servers.end(); server++)
	{
		fd_socket = (*server)->EstablishConnection();	
		//Add a file_descriptor to an fd_set
		FD_SET(fd_socket, &readfds);
		if(fd_socket > fd_max)
		{
			fd_max = fd_socket;
		}
	}

	while(true)
	{
		for(set<WebBrowsers*>::iterator iter1= Browsers.begin(); iter1 != Browsers.end(); iter1++)
		{
			// std::cout << "fd =" << fd << endl;
			fd	= (*iter1)->get_file_descriptor();	
			if(fd > fd_max)
			{
				fd_max = fd;
			}
		}
		/****
		 * The recv function is used to read incoming data on connection-oriented sockets,
		 * 
		*/
		//What if you’re blocking on an accept() call? How are you going to recv() data at the same time? “Use non-blocking sockets!” No way! You don’t want to be a CPU hog. What, then?
		/*****select() gives you the power to monitor several sockets at the same time. It’ll tell you which ones are ready for reading, which are ready for writing, and which sockets have raised exceptions, if you really want to know that.*/
		//select(fd_max + 1, &readfds, &writefds, NULL, 0);
		// std::cout << "ll\n";
		for (set<server*>::iterator iter2 = servers.begin(); iter2 != servers.end(); iter2++)
		{
			//When select() returns, readfds will be modified to reflect which of the file descriptors you selected which is ready for reading. You can test them with the macro FD_ISSET()
			//Return true if fd is in the set.
			if (FD_ISSET((*iter2)->get_fd_socket(), &readfds))
			{
				WebBrowsers *browser = new WebBrowsers((*iter2)->get_fd_socket());
				//(void) browser;
				Browsers.insert(browser);
				// FD_SET(browser->get_file_descriptor(), &readfds);
				// FD_SET(browser->get_file_descriptor(), &writefds);
				
			}
		}
		// for(set<WebBrowsers*>::iterator iter3 = Browsers.begin(); iter3 != Browsers.end(); iter3++ )
		// {
		// 	if(FD_ISSET((*iter3)->get_file_descriptor(), &readfds))
		// 	{
		// 		if((*iter3)->receive_data() == 2)
		// 		{
		// 			iter3 = Browsers.erase(iter3);
		// 			iter3--;
		// 		}
		// 	}
		// }

	}

	//handle multiple socket connections with fd_set and select 
	//When writing server programs using sockets , it becomes necessary to handle multiple connections at a time , since a server needs to serve multiple clients.

}


