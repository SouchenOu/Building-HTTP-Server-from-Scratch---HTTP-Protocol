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
		}else if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			value = 1;
			return 2;
		}
		if(request_Headers == NULL){
			read_buffer = read_buffer + buffer;
		}
		std::cout << "read_buffer:\n";
		//std::cout << read_buffer << endl;
		// if(request_Headers != NULL)
		// {
		// 	// request_Headers->give_head("Body") += buffer;
		// }
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
	status = request_Headers->get_indice();
	if(status == 0)
	{
		send_buffer = request_Headers->give_the_header(0 , 0);
		indice = 2;
		delete request_Headers;
		request_Headers = 0;

	}else if(status == 1)
	{
		std::cout << "enter here\n";
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
	int total = 10000;

	if(send_byte + total > send_buffer.size())
	{
		total = send_buffer.size() - send_byte;
	}
	send(file_descriptor, send_buffer.c_str() + send_byte, total, 0);
	send_byte = send_byte + total;

}







/******if (!already_calculated)
	{
		ifstream file(filepath.c_str(), ofstream::in);
		file.seekg(0, ios::end);
		fileSize = file.tellg();
	}*/

