/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:36:12 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:36:13 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/response.hpp"

#include "../headers/headers.hpp"

response::response()
{
		std::cout << "response\n";
}


response::~response()
{

}


int response::response_preparation(const std::set<server*> &servers, std::map<std::string, std::string> headers, std::string path)
{
	(void) servers;
	(void) path;
	(void) headers;
	// string Host;
	// unsigned int port;
	// string path_navigate;
	// path_navigate = path;
	// std::set<server*>::iterator iter1;
	// std::set<string>::iterator iter2;
	// this->Servers =  NULL;
	// std::cout << "yes\n";
	// if(headers.find("Host") != headers.end())
	// {
	// 	Host = headers.find("Host")->second;
	// }
	// else 
	// {
	// 	Host = "";
	// 	code = 400;
	// 	std::cout << "Bad request\n";
	// 	return 0;
	// }
	// //std::cout << "Host-->" << Host << endl;

	// if(headers.find("Port") != headers.end())
	// {
	// 	port = atoi(headers.find("Port")->second.c_str());
	// }else
	// {
	// 	port = 0;
	// 	code = 400;
	// 	return 0;
	// }
	// std::cout << "Port-->" << port << endl;
	// for(iter1 = servers.begin(); iter1 != servers.end(); iter1++)
	// {
	// 	set<string> server_names = (*iter1)->get_server_name();
	// 	for(iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
	// 	{
	// 		if((*iter2) == Host && (*iter1)->get_port_listen() == port)
	// 		{
	// 			this->Servers = (*iter1);
	// 		}
	// 	}

	// }

	// if(this->Servers == NULL)
	// {
	// 	std::cout << "No Server is compatible\n";
	// 	return 0;
	// }

	// //For location
	// std::list<Location> locations = Servers->get_locations();
	// if(locations.size() == 0)
	// {
	// 	Locations = NULL;
	// 	return 0;
	// }
	// //std::set<Location>::iterator i1;

	// for(std::list<Location>::iterator i1 = locations.begin(); i1 != locations.end() ; i1++)
	// {
	// 	if((i1)->get_path() == path_navigate)
	// 	{
	// 		this->Locations = new Location(*i1);
	// 		return 1;
	// 	}
	// }

	
	return 1;

}









