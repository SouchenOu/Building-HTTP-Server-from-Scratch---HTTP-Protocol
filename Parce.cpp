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
# define WHITESPACES "; \t"

void ccout(std::string message, string color = BLUE)
{
	std::time_t time = std::time(0);
	std::tm* time_rightnow = std::localtime(&time);

	std::cout << color << "[";

	std::cout << time_rightnow->tm_hour << ":" << time_rightnow->tm_min << ":" << time_rightnow->tm_sec << "]: " << message << RESET << std::endl;
}

void	parse_config_file(const string config_file)
{
	if (config_file.length() == 0)
	{
		ccout("Our config file is empty");
		exit (1);
	}
    ifstream read_file(config_file.c_str());
	// convert contents of a file to string.
	string convert_to_string((istreambuf_iterator<char>(read_file)), istreambuf_iterator<char>());
	read_file.close();
	const vector<string> config_line = ft_split(convert_to_string, "\n");
	if (!config_line.size())
	{
		ccout("Config file is empty");
		exit (1);
	}
	// Parse and add multiple _servers in "_servers"
	size_t count = 0;
	while (count < config_line.size())
	{
		vector<string> word_line = ft_split(config_line[count], WHITESPACES);
		if (word_line[0] == "server")
		{
			server *serv = parse_server(config_line, &count);
			if(serv != 0)
			{
				std::cout << BLUE  << server->get_root() << "--> ip_address:port/server_names conflict with another server" << endl;
				delete serv;
				exit(0);
			}
			for (list<server*>::const_iterator sserver = servers.begin(); sserver != servers.end(); sserver++)
			{
				if ((*sserver)->get_ip_address() == serv->get_ip_address() && (*sserver)->get_port() == serv->get_port)
				{
					list<string> server_names = (*sserver)->get_server_names();
					if (server_names.size() == 0 || serv->get_server_names().size() == 0)
					{
						std::cout << BLUE  << serv->get_root() << "--> ip_address:port/server_names conflict with another server" << endl;
						delete serv;
						exit(0);
					}
						
					for (list<string>::iterator server_name = server_names.begin(); server_name != server_names.end(); server_name++)
					{
						for (list<string>::const_iterator new_server_name = serv->get_server_names().begin(); new_server_name != serv->get_server_names().end(); new_server_name++)
						{
							if (*server_name == *new_server_name)
							{
								std::cout << BLUE  << server->get_root() << "--> ip_address:port/server_names conflict with another server" << endl;
								delete serv;
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



server	*parse_server(const vector<string> config_file, size_t *count)
{
	string address_ip;
	string address_port;

	vector<string> world1 = ft_split(config_file[0], WHITESPACES);

	if (world1[1] != "{")
	{
		return NULL;
	}
		

	//server *server = new server();

	vector<string>::const_iterator iter = config_file.begin() + *count;
	if (iter == config_file.end())
	{
		return NULL;
	}
		
	iter++;
	(*count)++;
	while (iter != config_file.end())
	{
		vector<string> words2 = ft_split(*iter, WHITESPACES);
		if (!words2.size())
		{
			iter++;
			(*count)++;
			continue;
		}
		if (words2[0][0] == '#')
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
		else if (words2[0] == "listen")
		{
			if (words2.size() != 2)
			{
				
					std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have another argument after listen" << endl;
					delete server;
					exit(0);
			}
			vector<string> listen_words = ft_split(words2[1], ":");
			
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
				
			server->set_ip_address(ip_address);

			if (is_integer(address_port) == 0)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: address port should be an integer" << endl;
				delete server;
				exit(0);
			}
			server->set_port(atoi(address_port.c_str()));

		}
		// server_name

		else if (words2[0] == "server_name")
		{
			if (words2.size() < 2)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have another argument after server_name" << endl;
				delete server;
				exit(0);
			}
			for (vector<string>::const_iterator server_name = words2.begin() + 1; server_name != words2.end(); server_name++)
			{
				server->push_in_server_name(*server_name);
			}
		}
		else if (words2[0] == "location")
		{
			if (words2.size() != 3)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have another argument after location" << endl;
				delete server;
				exit(0);
			}
			size_t old_count = *count;
			server->push_in_location(parse_location(config_file, count, server));
			iter = iter +  *count - old_count;
		}
		
		else if (words2[0] == "error_page")
		{
			if (words2.size() != 3)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have three argument after error_page" << endl;
				delete server;
				exit(0);
			}
			server->push_in_error_page(pair<unsigned int, string>((unsigned int)atoi(words2[1].c_str()), words2[2]));
		}
		else if (words2[0] == "index")
		{
			if (words2.size() != 2)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have another argument after index" << endl;
				delete server;
				exit(0);
			}
			server->set_index(words2[1]);
		}
		else if (words2[0] == "client_max_body_size")
		{
			if (words2.size() != 2)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have another argument after client_max_body_size" << endl;
				delete server;
				exit(0);
			}
			if (!is_integer(words2[1]))
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have a number after client_max_body_size" << endl;
				delete server;
				exit(0);
			}
			server->set_client_max_body_size(atoll(words2[1].c_str()));
		}

		else if (words2[0] == "cgi")
		{
			if (words2.size() != 3)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have three argument after cgi" << endl;
				delete server;
				exit(0);
			}
			server->push_in_cgi(words2[1], words2[2]);
		
		}
		
		else if (words2[0] == "root")
		{
			if (words2.size() != 2)
			{
				std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: should have another argument after root" << endl;
				delete server;
				exit(0);
			}
			string root_tmp = words2[1];
			if (root_tmp.size() > 0 && root_tmp[0] == '/')
				root_tmp = tmp.substr(1);
			if (root_tmp.size() > 1 && tmp[root_tmp.size() - 1] == '/')
				root_tmp.resize(root_tmp.size() - 1);
			server->set_root(root_tmp);
		}
		
	
		iter++;
		(*count)++;
	}
	vector<string> end_file = ft_split(*iter, WHITESPACES);
	while (!end_file.size() || end_file[0] != "}")
	{
		(*count)++;
		end_file = ft_split(config_file[*count], WHITESPACES);
	}
	if (end_file.size() && end_file[0] != "}")
	{
		std::cout << BLUE  << server->get_root() << "--> server configuration is invalid: missig close bracket" << endl;
		delete server;
		exit(0);
	}
	
	return server;
}

Location	parse_location(const vector<string> &config, size_t *count, Server *server)
{
	Location	location;
	vector<string> line = ft_split(config[*count], WHITESPACES);
	if (line.size() != 3)
		err_parsing_config(server, "expecting a directory and '{' after 'location'");
	string tmp = line[1];
	if (tmp.size() > 0 && tmp[0] != '/')
		tmp = '/' + tmp;
	if (tmp.size() > 1 && tmp[tmp.size() - 1] == '/')
		tmp.resize(tmp.size() - 1);
	location.set_path(tmp);
	DEBUG("\t" << location.get_path());
	if (line[2] != "{")
		err_parsing_config(server, "expecting '{' after 'location' directory");
	(*count)++;
	DEBUG("\t{");
	vector<string>::const_iterator it = config.begin() + *count;
	while (it != config.end())
	{
		vector<string> line = ft_split(*it, WHITESPACES);
		if (!line.size() || !line[0].size())
		{
			it++;
			(*count)++;
			continue;
		}
		if (line[0][0] == '#')
		{
			it++;
			(*count)++;
			continue;
		}
		else if (line[0].size() && line[0] != "}")
			DEBUG("\t\t" << line[0] << ":");
		if (line[0] == "}")
			break;
		else if (line[0] == "allow")
		{
			if (line.size() < 2)
				err_parsing_config(server, "expecting at least 1 argument after 'allow'");
			for (vector<string>::const_iterator allow_m = line.begin() + 1; allow_m != line.end(); allow_m++)
			{
				DEBUG("\t\t\t" << *allow_m);
				location.push_back_HTTP_method(*allow_m);
			}
		}
		else if (line[0] == "return")
		{
			if (line.size() != 3)
				err_parsing_config(server, "expecting 2 arguments after 'return'");
			if (location.get_HTTP_redirection_type() != 0)
				err_parsing_config(server, "only one redirection can be set for a given location");
			int type = atoi(line[1].c_str());
			if (!(type == 300 || type == 301 || type == 302 || type == 303 || type == 304 || type == 307 || type == 308))
				err_parsing_config(server, "redirection code is invalid");
			if (line[1].size())
			{
				location.set_HTTP_redirection_type(type);
				location.set_HTTP_redirection(line[2]);
				DEBUG("\t\t\t" << type << " " << line[2]);
			}
		}
		else if (line[0] == "root")
		{
			if (line.size() != 2)
				err_parsing_config(server, "expecting 1 argument after 'root'");
			string tmp = line[1];
			if (tmp.size() > 0 && tmp[0] != '/')
				tmp = '/' + tmp;
			if (tmp.size() > 1 && tmp[tmp.size() - 1] == '/')
				tmp.resize(tmp.size() - 1);
			location.set_root(tmp);
			DEBUG("\t\t\t" << tmp);
		}
		else if (line[0] == "index")
		{
			if (line.size() != 2)
				err_parsing_config(server, "expecting 1 argument after 'index'");
			location.set_index(line[1]);
			DEBUG("\t\t\t" << line[1]);
		}
		else if (line[0] == "autoindex")
		{
			if (line.size() != 2)
				err_parsing_config(server, "expecting 1 argument after 'autoindex'");
			if (line[1] == "0" || line[1] == "1")
			{
				location.set_autoindex(atoi(line[1].c_str()));
				DEBUG("\t\t\t" << location.get_autoindex());
			}
		}
		else
		{
			DEBUG("\t\t***OTHER LOCATION: " << line[0]);
		}
		it++;
		(*count)++;
	}
	vector<string> end = ft_split(config[*count], WHITESPACES);
	if (end[0] != "}")
	{
		cerr << location.get_path() << " location: missing closing bracket" << endl;
		exit(EXIT_FAILURE);
	}
	DEBUG("\t}");
	if (location.get_root().size() == 0)
		location.set_root(location.get_path());
	location.set_server(server);
	return location;
}


