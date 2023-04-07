/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:41:02 by souchen           #+#    #+#             */
/*   Updated: 2023/04/03 14:41:03 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEADERS_HPP
#define HEADERS_HPP


# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
#include <fcntl.h>
# include <unistd.h>
#include "string.h"

# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/socket.h> 

# include <vector>
#include <set>
# include <map>
# include "server.hpp"
#include "Location.hpp"

#define BLUE    "\033[34m"


class server;
class Location;
//# include "../webserver/parce_config_file.cpp"
//#include "../webserver/functions_help.cpp"
//#include "server.hpp"
//#include "../webserver/functions_help.cpp"


using namespace std;


vector<string> ft_divise(const std::string &str, const std::string &search_data);
server	*parse_server(vector<string> config_file, size_t *count);




#endif