/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define BLUE    "\033[34m"
# define isspace "; \t"
#include "../headers/server.hpp"


#include "functions_help.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>

using namespace std;



// convert .txt to string




server	*parse_server(vector<string> config_file, size_t *count)
{
	string address_ip;
	string address_port;
	size_t size;

	server *serv = new server();
	vector<string> world1 = ft_divise(config_file[0], isspace);

	if (world1[1] != "{")
	{
		cout << "Invalid config file\n";
		exit(0);
	}
		

	vector<string>::iterator iter = config_file.begin() + *count;
	if (iter == config_file.end())
	{
		return NULL;
	}
		
	iter++;
	(*count)++;
	while (iter != config_file.end())
	{
		vector<string> words2 = ft_divise(*iter, isspace);
		if (!words2.size() || words2[0][0] == '#')
		{
			iter++;
			(*count)++;
			continue;
		}
		if (words2[0] == "}")
		{
			break;
		}
	
			
		// listen
		// example     listen 127.0.0.1:8080;
		/**listen: The IP address / port combination that this server block is 
		 * designed to respond to. If a request is made by a client that matches these values,
		 *  this block will potentially be selected to handle the connection*/
		else if (words2[0] == "listen")
		{
			if (words2.size() != 2)
			{
				
					std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after listen" << endl;
					exit(0);
			}
			vector<string> listen_words = ft_divise(words2[1], ":");
			
			address_ip = listen_words[0];

			if (listen_words.size() == 1)
			{
				address_ip = "0.0.0.0";
				address_port = listen_words[0];
			}
			else if(listen_words.size() == 2)
			{
				address_port = listen_words[1];
			}
				
			if (address_ip == "localhost")
			{
				address_ip = "127.0.0.1";
			}
				
			serv->set_ip_address(address_ip);

			if (is_integer(address_port) == 0)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: address port should be an integer" << endl;
				exit(0);
			}
			serv->set_port_listen(atoi(address_port.c_str()));

		}
		// server_name
	/******server_name: This directive is the other component used to select a server block for processing. If there are multiple server blocks with listen directives of the same specificity that can handle the request,
	 * 
	 *  Nginx will parse the “Host” header of the request and match it against this directive.*/
		else if (words2[0] == "server_name")
		{
			if (words2.size() < 2)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after server_name" << endl;
				exit(0);
			}
			for (vector<string>::iterator server_name = words2.begin() + 1; server_name != words2.end(); server_name++)
			{
				serv->push_in_server_name(*server_name);
			}
		}
		
		else if (words2[0] == "error_page")
		{
			if (words2.size() != 3)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have three argument after error_page" << endl;
				exit(0);
			}
			serv->push_in_error_page(pair<unsigned int, string>((unsigned int)atoi(words2[1].c_str()), words2[2]));
		}
		else if (words2[0] == "index")
		{
			if (words2.size() != 2)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after index" << endl;
		
				exit(0);
			}
			serv->set_index(words2[1]);
		}
		//we will increase the size limit of the file limit in Nginx to any size you want by using 
		// client_max_body_size
		else if (words2[0] == "client_max_body_size")
		{
			if (words2.size() != 2)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after client_max_body_size" << endl;
				exit(0);
			}
			if (!is_integer(words2[1]))
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have a number after client_max_body_size" << endl;
	
				exit(0);
			}
			serv->set_client_max_body_size(atoi(words2[1].c_str()));
		}
		/******Nginx fastcgi is used to translate requests of clients from an application server which was not handled the request of the client directly.*/
		/****We can say that the nginx fastcgi protocol means improving the performance by running each request in a process that was separate in nginx.*/

		//CGI was the earliest common method available that allowed a web page to be interactive
		else if (words2[0] == "cgi")
		{
			if (words2.size() != 3)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have three argument after cgi" << endl;
				exit(0);
			}
			serv->push_in_cgi(words2[1], words2[2]);
		
		}
		
		else if (words2[0] == "root")
		{
			if (words2.size() != 2)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after root" << endl;

				exit(0);
			}
			string root_tmp = words2[1];
			if (root_tmp.size() > 0 && root_tmp[0] == '/')
				root_tmp = root_tmp.substr(1);
			if (root_tmp.size() > 1 && root_tmp[root_tmp.size() - 1] == '/')
				root_tmp.resize(root_tmp.size() - 1);
			serv->set_root(root_tmp);
		}

		/***** each location is used to handle a certain type of client request,
		 *  and each location is selected by matching the location definition against the client request through a selection algorithm.*/


		/*****NGINX’s location setting helps you set up the way in which NGINX responds to requests for resources inside the server.*/

		//One or more location contexts in a server context define how to process specific sets of URIs.
		else if (words2[0] == "location")
		{
			Location location;
			if (words2.size() != 3)
			{
				std::cout << BLUE  << serv->get_root() << "--> server configuration is invalid: should have another argument after location" << endl;

				exit(0);
			}
			size_t old_count = *count;

			// we shouls parse location
			string t;
			string path;
			t = words2[1];
		
			if(t.size() > 1 && t[t.size() - 1] == '/')
			{
				t.resize(t.size() - 1);
			} 
			if(words2[2] != "{")
			{
				std::cout << BLUE  << serv->get_root() << "--> should have open bracket after location and path" << endl;
				exit(0);
			}

			path = t;
			*count++;
			vector<string>::iterator iter2 = config_file.begin() + *count;
			while(iter != config_file.end())
			{
				vector<string> line = ft_divise(*iter, isspace);
				if(line.size() == 0 || line[0][0] == '#')
				{
					iter++;
					*count++;
					continue;
				}
				if(line[0] ==  "}")
				{
					break ;
				}
				// root in location
				if(line[0] == "root")
				{
					if(line.size() != 0)
					{
						std::cout << BLUE  << serv->get_root() << "--> should have another argument after root" << endl;
						exit(0);
					}

					if(line[1].size() > 0 && line[1][line[1].size() - 1] == '/')
					{
						line[1].resize(line[1].size() - 1);
					}
					location.set_root(line[1]);
				}
				// try_files in location 
				if(line[0] == "try_files")
				{
					if(line.size() < 2)
					{
						std::cout << BLUE  << serv->get_root() << "--> should have minimum one argument after try_files argument" << endl;
						exit(0);
					}
					if(line[1].size() > 0 && line[1][line[1].size() - 1] == '/')
					{
						line[1].resize(line[1].size() - 1);
					}
					location.set_try_files(line[1]);
				}
				// alias in location 

				if(line[0] == "alias")
				{
					if(line.size() != 2)
					{
						std::cout << BLUE  << serv->get_root() << "--> should have another argument after alias" << endl;
						exit(0);
					}
					if(line[1].size() > 0 && line[1][line[1].size() - 1] == '/')
					{
						line[1].resize(line[1].size() - 1);
					}
					location.set_alias(line[1]);
				}

				// return in location
				if(line[0] == "return")
				{
					if(line.size() != 3)
					{
						std::cout << BLUE  << serv->get_root() << "--> should have two argument after return" << endl;
						exit(0);
					}
					if(line[2].size() > 0 && line[2][line[2].size() - 1] == '/')
					{
						line[2].resize(line[2].size() - 1);
					}
					int number = atoi(line[1].c_str());

					if(number == 301 || number == 307)
					{
						std::cout << BLUE  << serv->get_root() << "--> invalid number" << endl;
						exit(0);
					}

					location.set_return_line(line[2]);
					
					

				}



			}



			serv->push_in_location(location);
			iter = iter +  *count - old_count;
		}
		
		
	
		iter++;
		(*count)++;
	}
	// vector<string> end_file = ft_divise(*iter, isspace);
	// while (!end_file.size() || end_file[0] != "}")
	// {
	// 	(*count)++;
	// 	end_file = ft_divise(config_file[*count], isspace);
	// }
	// if (end_file.size() && end_file[0] != "}")
	// {
	// 	std::cout << BLUE  << serv.get_root() << "--> server configuration is invalid: missig close bracket" << endl;
	// 	exit(0);
	// }
	
	return serv;
}










