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
#include "../headers/request.hpp"


#define BUFFUR_SIZE 4096

// WebBrowsers::WebBrowsers()
// {
// 	file_descriptor = 0;
// 	//file_descriptor = 0;
// 	std::cout << "hello, thie is new client\n";
// }

WebBrowsers::WebBrowsers(int fd_socket, std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request_Headers(0),indice(0)
{
	
	std::cout << "Connection......\n";
    Connection(fd_socket);


	
}
WebBrowsers::~WebBrowsers()
{
		// Log("Client disconnected");
	std::cout << "destructer\n";
	if (file_descriptor > 0)
		close(file_descriptor);
	if (request_Headers != 0)
	{
		delete request_Headers;
		request_Headers = 0;
	}

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
		inet_ntop(AF_INET, &(address_client.sin_addr), client_ipv4_str, INET_ADDRSTRLEN);

}
int WebBrowsers::Read_request()
{

	std::cout << "read_request\n";
		int recv_s;
		char buffer[BUFFUR_SIZE];
		std::string read_buffer;
		value = 0;

		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/
				
		recv_s = recv(file_descriptor, buffer,BUFFUR_SIZE, 0 ); 
				//std::cout << buffer << endl;

		if(recv_s < 0)
		{
			std::cout << "No message are available to be received\n";
			value = 1;
			return 2;
		}else if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			value = 1;
			return 2;
		}
		if(request_Headers == NULL)
		{
			read_buffer = read_buffer + buffer;
		}
		std::cout << "read_buffer:\n";
		std::cout << read_buffer << endl;
		// if(request_Headers != NULL)
		// {
		// 	// request_Headers->give_head("Body") += buffer;
		// }
;		// If the datagram or message is not larger than the buffer specified,
		if(recv_s < BUFFUR_SIZE)
		{		
			// send request
			if(request_Headers == NULL)
			{
				request_Headers = new Request(read_buffer);
			}
			read_buffer.clear();
			value = 1;
		}
	return value;
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
int WebBrowsers::get_indice()
{
	return indice;
}

// setters

void WebBrowsers::set_file_descriptor(int fd)
{
    file_descriptor = fd;
}


// some used functions

void WebBrowsers::check_request()
{
	send_byte = 0;
	//Response->response_preparation(servers, request_Headers->get_headers(), request_Headers->get_Path());
	request_Headers->check_request_with_config_file(servers);

	//file_path
	request_Headers->path_of_file();
	int status;
	status = request_Headers->get_indice(file_file_descriptor);
	// std::cout << "status -->" << status << endl;
	// file_file_descriptor = open(static_cast<const char *>(path.c_str()), O_RDONLY);
	if(status == 0)
	{
		send_buffer = request_Headers->give_the_header(0 , 0);
		indice = 2;
		delete request_Headers;
		request_Headers = 0;

	}
	

	
	




}
void WebBrowsers::send_response()
{
	
	if(indice == 2)
	{
		send2();
	}
}



void WebBrowsers::send2()
{
	int fd;
	//char hello[100] = "hello souchen";
	char 	buff[BUFFUR_SIZE];
	if(file_file_descriptor == 0)
	{
		std::cout << "error1\n";
	}
	fd = read(file_file_descriptor, buff, BUFFUR_SIZE);
	std::cout << "buffer->" << buff << endl;
	std::cout << "fd = " << fd << endl;
	if(fd <= 0)
	{
		std::cout << "error\n";
	}
	std::string str = "HTTP/1.1 200 OK\r\nContent-Length: 278\r\n\r\n";
	send(file_descriptor, str.c_str(), str.length(), 0);
	send(file_descriptor, buff, fd, 0);
	//write(file_descriptor, hello, strlen(hello));

	if (fd < BUFFUR_SIZE)
	{
		std::cout << "sendig file to client !\n";
		close(file_file_descriptor);
		delete(request_Headers);
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request_Headers = NULL;
	}

}



