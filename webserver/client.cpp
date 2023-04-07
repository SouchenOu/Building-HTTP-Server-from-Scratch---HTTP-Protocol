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

#include "../headers/client.hpp"
#include "../headers/server.hpp"

Clients::Clients(){}

Clients::Clients(int fd_socket, set<server*>& servers) : file_descriptor(0)
{
	// struct sockaddr_in *address = get_address_client();
    int addrlen = sizeof(address_client);
	file_descriptor = accept(fd_socket,get_address_client(), (socklen_t*)&addrlen);
}
Clients::~Clients()
{

}

//getters

int Clients::get_file_descriptor()
{
	return file_descriptor;
}

struct sockaddr* Clients::get_address_client(void)
{
	return (struct sockaddr*)(&address_client);
}



