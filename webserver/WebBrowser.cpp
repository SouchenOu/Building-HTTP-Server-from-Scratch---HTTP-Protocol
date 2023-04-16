/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebBrowser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:23:29 by souchen           #+#    #+#             */
/*   Updated: 2023/04/06 14:23:30 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/WebBrowser.hpp"
#include "../headers/server.hpp"
#include "../headers/Request.hpp"

// WebBrowsers::WebBrowsers()
// {
// 	file_descriptor = 0;
// 	//file_descriptor = 0;
// 	std::cout << "hello, thie is new client\n";
// }

WebBrowsers::WebBrowsers(int fd_socket, std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request_Headers(0)
{
	
	std::cout << "Connection......\n";
    Connection(fd_socket);


	
}
WebBrowsers::~WebBrowsers()
{

}

void WebBrowsers::Connection(int fd_socket)
{
	int addrlen = sizeof(address_client);
	//The accept() system call is used to process each connection thread in the queue created by listen()
	//Accept incoming client connections.
	file_descriptor = accept(fd_socket, get_address_client(), (socklen_t*)&addrlen);
	if(file_descriptor < 0)
	{
		std::cout << "server failed to accept incoming connection " << endl;
        check_fd = -1; 
	}
}
int WebBrowsers::Read_request()
{

	std::cout << "read_request\n";
		int recv_s;
		char buffer[10000];
		std::string read_buffer;
		value = 0;

		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/
				
		recv_s = recv(file_descriptor, buffer, 10000, 0 ); 
				//std::cout << buffer << endl;

		if(recv_s < 0)
		{
			std::cout << "No message are available to be received\n";
			value = 1;
			return 2;
		}if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			value = 1;
			return 2;
		}
		else{
			read_buffer = read_buffer + buffer;
		}
		std::cout << "read_buffer:\n";
		std::cout << read_buffer << endl;
		if(request_Headers != NULL)
		{
			// request_Headers->give_head("Body") += buffer;
		}
;		// If the datagram or message is not larger than the buffer specified,
		if(recv_s < 10000)
		{		
			// send request
			if(request_Headers == NULL)
			{
				request_Headers = new Request(read_buffer);
			}
			read_buffer.clear();
			value = 1;
		}
	return 1;
}




int WebBrowsers::get_check_fd()
{
    return check_fd;
}

struct sockaddr* WebBrowsers::get_address_client(void)
{
    return (struct sockaddr*)(&address_client);
}

int WebBrowsers::get_file_descriptor()
{
    return file_descriptor;
}

int WebBrowsers::get_value()
{
	return value;
}

// setters

void WebBrowsers::set_file_descriptor(int fd)
{
    file_descriptor = fd;
}


// some used functions

void WebBrowsers::check_request()
{
	//Response->response_preparation(servers, request_Headers->get_headers(), request_Headers->get_Path());
	check_request_with_config_file(servers,request_Headers->get_headers(), request_Headers->get_Path());

	

}


int WebBrowsers::check_request_with_config_file(const std::set<server*> &servers, std::map<std::string, std::string> headers, std::string path)
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











/******
 * if (!already_calculated)
	{
		ifstream file(filepath.c_str(), ofstream::in);
		file.seekg(0, ios::end);
		fileSize = file.tellg();
	}
	DEBUG("GET HEADER");
	DEBUG("CODE IS " << code);
	stringstream header;
	header << "HTTP/1.1 " << codes[code] << endl;
	header << "Date: " << get_time_stamp() << endl;
	header << "Server: webserv/0.01" << endl;
	header << "Content-Type: " << ::get_type(filepath, passed_cgi || already_calculated) << endl;
	header << "Content-Length: " << fileSize << endl;
	header << "Connection: Closed" << endl;
	if (location && location->get_HTTP_redirection_type() > 0)
		header << "Location: " << location->get_HTTP_redirection() << endl;
	header << endl;
	DEBUG("RET HEADER :" << header.str());
	return (header.str());*/