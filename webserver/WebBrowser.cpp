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

WebBrowsers::WebBrowsers(int fd_socket, std::set<server*>& servers ) : servers(servers),request_Headers(0)
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
		// std::cout << "read_buffer :\n";
		// std::cout << read_buffer << endl;
		// If the datagram or message is not larger than the buffer specified,
		if(recv_s < 10000 && recv_s > 0)
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



// setters

void WebBrowsers::set_file_descriptor(int fd)
{
    file_descriptor = fd;
}


// some used functions

void WebBrowsers::set_request(std::map<std::string, std::string> headers, std::string path)
{
	Response->response_preparation(servers, headers, path);
}

