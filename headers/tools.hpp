/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:41:02 by souchen           #+#    #+#             */
/*   Updated: 2023/04/03 14:41:03 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TOOLS_HPP
#define TOOLS_HPP


// # include <iostream>
// # include <fstream>
// # include <sstream>
// # include <string>
// # include <cstdlib>
// #include <fcntl.h>
// # include <unistd.h>
// #include "string.h"

// # include <netinet/in.h>
// # include <arpa/inet.h>
// # include <sys/select.h>
// # include <sys/socket.h> 
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
# include <vector>
#include <set>
# include <map>
# include <list>
# include "server.hpp"
#include "WebBrowser.hpp"
#include "location.hpp"
#include "request.hpp"
#include "response.hpp"

#define BLUE    "\033[34m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"


class server;
class Location;
//# include "../webserver/parce_config_file.cpp"
//#include "../webserver/functions_help.cpp"
//#include "server.hpp"
//#include "../webserver/functions_help.cpp"


using namespace std;


vector<string> ft_divise(const std::string &str, const std::string &search_data);
server	*parse_server(vector<string> config_file, size_t *count);
bool is_directory(const string &filename);
Location	parse_location(vector<string> &config_file, size_t *cmp);



#endif