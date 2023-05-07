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
#include "../headers/tools.hpp"

response::response()
{
		std::cout << "response\n";
}


response::~response()
{

}


	/*************************************************/
    /*  HTTP consists of requests and responses.     */
    /*  When a client (such as a web browser) 
	/*	wants to retrieve a webpage from a server,	*/
	/* 	it sends an HTTP request to the server. 	*/
	/*	The server then processes the request and	*/
	/*	 sends back an HTTP response. 				*/
    /*            									 */
    /*************************************************/


std::string response::response_header(int size_of_file, bool var, std::string path_access, int status_code, map<unsigned int, string> map_Codestatus)
{
	// std::cout << "path_access--->" << path_access << endl;
	if(var == 0)
	{
		ifstream our_file(path_access.c_str(),std::ios::in);
		our_file.seekg(0, ios::end);
		//Say we have entered 20 characters in a text file, and you want to read it.
//		But along with reading you also want to know the position of the last position in the text file.
		size_of_file = our_file.tellg();
	}

	stringstream response_header;
    response_header << "HTTP/1.1 " << map_Codestatus[status_code] << endl;
	// //response_header << "Date: " << << endl;
	response_header << "Server: webserv/0.01" << endl;
	// response_header << "Content_type: text/html; charset=UTF-8"<< endl;
	// response_header << "X-Powered-By: PHP/8.1.12" << endl;
	response_header << "Content-Length: " << size_of_file << endl;
	// response_header << "Connection: Closed" << endl;
	response_header << endl;

	return response_header.str();

}









