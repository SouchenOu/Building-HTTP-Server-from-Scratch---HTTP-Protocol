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

WebBrowsers::WebBrowsers(int fd_socket, std::set<server*>& servers):servers(servers)
{
	// std::cout<< "here\n";
	// // struct sockaddr_in *address = get_address_client();
    // int addrlen = sizeof(address_client);
	// //The accept() system call is used to process each connection thread in the queue created by listen()
	// //Accept incoming client connections.
	// file_descriptor = accept(fd_socket,get_address_client(), (socklen_t*)&addrlen);
	// if(file_descriptor < 0)
	// {
	// 	std::cout << "server failed to accept incoming connection " << endl;
    //     check_fd = -1; 
	// }
	std::cout << "Connection......\n";
	client_len = sizeof(address_client);
	file_descriptor = accept(fd_socket, get_address_client(), get_addr_len() );
	inet_ntop(AF_INET, &(address_client.sin_addr), client_ipv4_str, INET_ADDRSTRLEN);

	
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
	std::cout << "reading->" << buffer << endl;

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

socklen_t			*WebBrowsers::get_addr_len(void)
{
	return (&client_len);
}

// setters

void WebBrowsers::set_file_descriptor(int fd)
{
    file_descriptor = fd;
}


