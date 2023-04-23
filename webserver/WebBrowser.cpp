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

WebBrowsers::WebBrowsers(int fd_socket, std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request_Headers(0),indice(0)
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
		char buffer[100000];
		std::string read_buffer;
		value = 0;

		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/
				
		recv_s = recv(file_descriptor, buffer, 100000, 0 ); 
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
			read_buffer = read_buffer + string(buffer, recv_s);
		}
		std::cout << "read_buffer:\n";
		//std::cout << read_buffer << endl;
		// if(request_Headers != NULL)
		// {
		// 	// request_Headers->give_head("Body") += buffer;
		// }
;		// If the datagram or message is not larger than the buffer specified,
		if(recv_s < 100000)
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
		std::cout << "Response: " << endl;
		std::cout << send_buffer << endl;
		indice = 2;
		delete request_Headers;
		request_Headers = 0;

	}else if(status == 1)
	{
		string test;
		request_Headers->index_auto(test);
		send_buffer = request_Headers->give_the_header(test.size() , 1);
		send_buffer = send_buffer + test;
		indice = 2;
		delete request_Headers;
		request_Headers = 0;
	}
	
	




}
void WebBrowsers::send_response()
{
	if(indice == 2)
	{
		send1();
	}
	else if(indice == 3)
	{
		send2();
	}
}


void WebBrowsers::send1()
{
	int total = 100000;
	//std::cout << "size->" << send_buffer.size() << endl;
	if(send_byte + total > send_buffer.size())
	{
		total = send_buffer.size() - send_byte;
	}
	::send(file_descriptor, send_buffer.c_str() + send_byte, total, 0);
	send_byte = send_byte + total;
	if (send_byte == send_buffer.size())
	{
		send_buffer.clear();
		indice = 3;
	}

}
void WebBrowsers::send2()
{
	int fd;
	char 	buff[100000];
	if(file_file_descriptor == 0)
	{
		std::cout << "error1\n";
	}
	fd = read(file_file_descriptor, buff, 100000);
	//std::cout << "buffer->" << buff << endl;

	if(fd <= 0)
	{
		std::cout << "error\n";
	}
	::send(file_descriptor, buff, fd, 0);
	//write(file_descriptor, "hello", 100000);

	if (fd < 100000)
	{
		//std::cout << "enter here !\n";
		close(file_file_descriptor);
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request_Headers = NULL;
	}

}



