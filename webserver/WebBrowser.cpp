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

WebBrowsers::WebBrowsers(){}

WebBrowsers::WebBrowsers(int fd_socket) : file_descriptor(0)
{
	// struct sockaddr_in *address = get_address_client();
    int addrlen = sizeof(address_client);
	//The accept() system call is used to process each connection thread in the queue created by listen()
	//Accept incoming client connections.
	file_descriptor = accept(fd_socket,get_address_client(), (socklen_t*)&addrlen);
	if(file_descriptor < 0)
	{
		std::cout << "server failed to accept incoming connection " << endl; 
	}
}
WebBrowsers::~WebBrowsers()
{

}

//getters

int WebBrowsers::get_file_descriptor()
{
	return file_descriptor;
}

 
void WebBrowsers::set_file_descriptor(int fd)
{
    this->file_descriptor = fd;
}


struct sockaddr* WebBrowsers::get_address_client(void)
{
	return (struct sockaddr*)(&address_client);
}



