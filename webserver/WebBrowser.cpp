/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
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
// 	std::cout << "hello, thie is new client\n";
// }

WebBrowsers::WebBrowsers(int fd_socket) : file_descriptor(0), recvStatus(0), read_buffer(0)
{
	std::cout<< "here\n";
	check_fd = 0;
	// struct sockaddr_in *address = get_address_client();
    int addrlen = sizeof(address_client);
	//The accept() system call is used to process each connection thread in the queue created by listen()
	//Accept incoming client connections.
	file_descriptor = accept(fd_socket,get_address_client(), (socklen_t*)&addrlen);
	if(file_descriptor < 0)
	{
		std::cout << "server failed to accept incoming connection " << endl;
		check_fd = -1;
	}
}
WebBrowsers::~WebBrowsers()
{

}

int WebBrowsers::receive_data()
{

	int recv_s;
	char buffer[1000];
	value = 0;

	recv_s = recv(file_descriptor, buffer, 1000, 0 ); 
	std::cout << "reading->" << recv_s << endl;

	if(recv_s <= 0)
	{
		std::cout << "No message are available to be received\n";
		value = 1;
		return 2;
	}else{
		read_buffer = read_buffer + string(buffer, recv_s);
	}

	if(recv_s < 1000)
	{
		// send request
		// if(request == 0)
		// {
		// 	request = new Request(recv_s);
		// }
		// read_buffer.clear();
		value = 1;
	}
	return value;

}






//getters

int WebBrowsers::get_file_descriptor()
{
	return file_descriptor;
}

struct sockaddr* WebBrowsers::get_address_client(void)
{
	return (struct sockaddr*)(&address_client);
}

int WebBrowsers::get_recvStatus()
{
	return recvStatus;
}

int WebBrowsers::get_value()
{
	return value;
}

int WebBrowsers::get_check_fd()
{
	return check_fd;
}

void WebBrowsers::set_file_descriptor(int fd)
{
    this->file_descriptor = fd;
}

void WebBrowsers::set_recvStatus(int recvStatus)
{
	this->recvStatus = recvStatus;
}





