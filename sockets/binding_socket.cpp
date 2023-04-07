/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding_socket.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:43:26 by souchen           #+#    #+#             */
/*   Updated: 2023/03/17 15:43:28 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binding_socket.hpp"





ft::BindingSocket::BindingSocket(int domain, int type, int protocol, int port, u_long ip_address) : SocketSimple(domain, type, protocol, port, ip_address)
{

        set_connection(connect_to_network(get_ident_socket(), get_address()));
        test_connection(get_connection());

}


// the structure sockaddr is a generic  container that just allows the OS to be able to read the first couple of bytes that 
// identify the address family.

// The address family determines what variant of the sockaddr struct to use that contains elements that make sense for that specific communication type. we use struct sockaddr_in, wich is defined in the header netinet/in.h
int ft::BindingSocket::connect_to_network(int identify_sock, struct sockaddr_in address)
{
    return bind(identify_sock, (struct sockaddr *)&address, sizeof(address));
}


// build our binding socket
// Our binding socket was what would connect to the network, and actually bind itself to it with this name.

// now we are going to add an extension to that which is the listening capability, now listening is where this socket is going to be connected to the network on a certain port, and it is going to wait for incoming connection 